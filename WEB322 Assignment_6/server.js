/******************************************************************************
                             WEB322 – Assignment 6
Full Name  : Sang Hyon Jeon
Student ID#: 113552194
Email      : shjeon5@myseneca.ca
Section    : NGG
Date       : April 7, 2023

Authenticity Declaration:
I declare that this assignment is my own work in accordance with Seneca
Academic Policy. I have done all the coding by myself and only copied the code
that my professor provided to complete this assignment.

Online (Cyclic) Link:   
******************************************************************************/
const express = require("express");
const multer = require("multer");
const cloudinary = require("cloudinary").v2;
const streamifier = require("streamifier");
const exphbs = require("express-handlebars");
const stripJs = require("strip-js");
const path = require("path");
const blogData = require("./blog-service.js");
const authData = require("./auth-service.js");
const clientSessions = require("client-sessions");

// The server must make use of the "express" module
const app = express();

// The server must listen on process.env.PORT || 8080
const HTTP_PORT = process.env.PORT || 8080;

// no { storage: storage } since we are not using disk storage
const upload = multer();

// Set the Cloudinary config to use your "Cloud Name", "API Key" and "API Secret" values
cloudinary.config({
  cloud_name: "dpju16bxg",
  api_key: "528451683481667",
  api_secret: "gU9teO1Y7g3BGj-yisQdph-xEag",
  secure: true,
});

// Register handlebars as the rendering engine for views
app.engine(
  ".hbs",
  exphbs.engine({
    extname: ".hbs",
    helpers: {
      // If app.locals.activeRoute matches the provided url, render the correct <li> element
      // and add the class "active"
      navLink: function (url, options) {
        return (
          "<li" +
          (url == app.locals.activeRoute ? ' class="active" ' : "") +
          '><a href="' +
          url +
          '">' +
          options.fn(this) +
          "</a></li>"
        );
      },

      // Exactly like the "if" helper, but with the added benefit of
      // evaluating a simple expression for equality
      equal: function (lvalue, rvalue, options) {
        if (arguments.length < 3)
          throw new Error("Handlebars Helper equal needs 2 parameters");
        if (lvalue != rvalue) {
          return options.inverse(this);
        } else {
          return options.fn(this);
        }
      },

      // Removes unwanted JavaScript code from our post body string
      safeHTML: function (context) {
        return stripJs(context);
      },

      // Helps keep our date formatting consistent in the views
      formatDate: function (dateObj) {
        let year = dateObj.getFullYear();
        let month = (dateObj.getMonth() + 1).toString();
        let day = dateObj.getDate().toString();
        return `${year}-${month.padStart(2, "0")}-${day.padStart(2, "0")}`;
      },
    },
  })
);
app.set("view engine", ".hbs");

// For your server to correctly return the "/css/main.css" file, the "static"
// middleware must be used
app.use(express.static("public"));

app.use(
  clientSessions({
    cookieName: "session",
    secret: "WEB322_Assignment_6",
    duration: 2 * 60 * 1000, // 2 minutes
    activeDuration: 60 * 1000, // 1 minute
  })
);

app.use(function (req, res, next) {
  res.locals.session = req.session;
  next();
});

// Since categories does not require users to upload an image, we should also
// include the regular express.urlencoded() middleware
app.use(express.urlencoded({ extended: true }));

// Add the property "activeRoute" to "app.locals" whenever the route changes
// If the blog is currently viewing a category, that category will be set in "app.locals"
app.use(function (req, res, next) {
  let route = req.path.substring(1);
  app.locals.activeRoute =
    "/" +
    (isNaN(route.split("/")[1])
      ? route.replace(/\/(?!.*)/, "")
      : route.replace(/\/(.*)/, ""));
  app.locals.viewingCategory = req.query.category;
  next();
});

// The default route "/" must redirect the user to the "/blog" route
app.get("/", (req, res) => {
  res.redirect("/blog");
});

// The route "/about" must return the about.html file from the views folder
app.get("/about", (req, res) => {
  res.render("about");
});

// Provided
app.get("/blog", async (req, res) => {
  // Declare an object to store properties for the view
  let viewData = {};

  try {
    // declare empty array to hold "post" objects
    let posts = [];

    // if there's a "category" query, filter the returned posts by category
    if (req.query.category) {
      // Obtain the published "posts" by category
      posts = await blogData.getPublishedPostsByCategory(req.query.category);
    } else {
      // Obtain the published "posts"
      posts = await blogData.getPublishedPosts();
    }

    // sort the published posts by postDate
    posts.sort((a, b) => new Date(b.postDate) - new Date(a.postDate));

    // get the latest post from the front of the list (element 0)
    let post = posts[0];

    // store the "posts" and "post" data in the viewData object (to be passed to the view)
    viewData.posts = posts;
    viewData.post = post;
  } catch (err) {
    viewData.message = "no results";
  }

  try {
    // Obtain the full list of "categories"
    let categories = await blogData.getCategories();

    // store the "categories" data in the viewData object (to be passed to the view)
    viewData.categories = categories;
  } catch (err) {
    viewData.categoriesMessage = "no results";
  }

  // render the "blog" view with all of the data (viewData)
  res.render("blog", { data: viewData });
});

// Nearly identical to the app.get('/blog')… route
// However, instead of using the most recent blog post, it uses the blog post with
// the id obtained from the route parameter
app.get("/blog/:id", async (req, res) => {
  // Declare an object to store properties for the view
  let viewData = {};

  try {
    // declare empty array to hold "post" objects
    let posts = [];

    // if there's a "category" query, filter the returned posts by category
    if (req.query.category) {
      // Obtain the published "posts" by category
      posts = await blogData.getPublishedPostsByCategory(req.query.category);
    } else {
      // Obtain the published "posts"
      posts = await blogData.getPublishedPosts();
    }

    // sort the published posts by postDate
    posts.sort((a, b) => new Date(b.postDate) - new Date(a.postDate));

    // store the "posts" and "post" data in the viewData object (to be passed to the view)
    viewData.posts = posts;
  } catch (err) {
    viewData.message = "no results";
  }

  try {
    // Obtain the post by "id"
    viewData.post = await blogData.getPostById(req.params.id);
  } catch (err) {
    viewData.message = "no results";
  }

  try {
    // Obtain the full list of "categories"
    let categories = await blogData.getCategories();

    // store the "categories" data in the viewData object (to be passed to the view)
    viewData.categories = categories;
  } catch (err) {
    viewData.categoriesMessage = "no results";
  }

  // render the "blog" view with all of the data (viewData)
  res.render("blog", { data: viewData });
});

// This route "/posts" gets posts within posts.json by category, minDate, or just all the posts
app.get("/posts", authData.ensureLogin, (req, res, next) => {
  let category = req.query.category;
  let minDate = req.query.minDate;
  let returnedPromise = null;

  if (category) {
    returnedPromise = blogData.getPostsByCategory(category);
  } else if (minDate) {
    returnedPromise = blogData.getPostsByMinDate(minDate);
  } else {
    returnedPromise = blogData.getAllPosts();
  }

  returnedPromise
    .then((data) => {
      if (data.length > 0) {
        res.render("posts", { posts: data });
      } else {
        res.render("posts", { message: "no results" });
      }
    })
    .catch((err) => {
      res.render("posts", { message: "no results" });
    });
});

// This route will return a JSON formatted string containing a single post whose id matches the value
app.get("/post/:id", authData.ensureLogin, (req, res, next) => {
  let postId = req.params.id;

  blogData
    .getPostById(postId)
    .then((data) => {
      if (data.length > 0) {
        res.render("posts", { posts: data });
      } else {
        res.render("posts", { message: "no results" });
      }
    })
    .catch((err) => {
      res.render("posts", { message: "no results" });
    });
});

// This route "/categories" gets all categories within the categories.json
app.get("/categories", authData.ensureLogin, (req, res, next) => {
  blogData
    .getCategories()
    .then((data) => {
      if (data.length > 0) {
        res.render("categories", { categories: data });
      } else {
        res.render("categories", { message: "no results" });
      }
    })
    .catch((err) => {
      res.render("categories", { message: "no results" });
    });
});

// This route simply sends the file "/views/addCategory.html"
app.get("/categories/add", authData.ensureLogin, (req, res, next) => {
  res.render("addCategory");
});

// POST route for adding a category
app.post("/categories/add", authData.ensureLogin, (req, res, next) => {
  blogData
    .addCategory(req.body)
    .then(() => {
      res.redirect("/categories");
    })
    .catch((err) => {
      res.status(500).send("Error adding category");
    });
});

// GET route for deleting a category by id
app.get("/categories/delete/:id", authData.ensureLogin, (req, res, next) => {
  let categoryId = req.params.id;

  blogData
    .deleteCategoryById(categoryId)
    .then(() => {
      res.redirect("/categories");
    })
    .catch((err) => {
      res.status(500).send("Unable to remove category / category not found");
    });
});

// GET route for deleting a post by id
app.get("/posts/delete/:id", authData.ensureLogin, (req, res, next) => {
  let postId = req.params.id;

  blogData
    .deletePostById(postId)
    .then(() => {
      res.redirect("/posts");
    })
    .catch((err) => {
      res.status(500).send("Unable to remove post / post not found");
    });
});

// This route simply sends the file "/views/addPost.html"
app.get("/posts/add", authData.ensureLogin, (req, res, next) => {
  blogData
    .getCategories()
    .then((data) => {
      res.render("addPost", { categories: data });
    })
    .catch((err) => {
      res.render("addPost", { categories: [] });
    });
});

// Most of this function was provided
app.post(
  "/posts/add",
  authData.ensureLogin,
  upload.single("featureImage"),
  (req, res, next) => {
    if (req.file) {
      let streamUpload = (req) => {
        return new Promise((resolve, reject) => {
          let stream = cloudinary.uploader.upload_stream((error, result) => {
            if (result) {
              resolve(result);
            } else {
              reject(error);
            }
          });

          streamifier.createReadStream(req.file.buffer).pipe(stream);
        });
      };

      async function upload(req) {
        let result = await streamUpload(req);
        console.log(result);
        return result;
      }

      upload(req).then((uploaded) => {
        processPost(uploaded.url);
      });
    } else {
      processPost("");
    }

    // Process the req.body and add it as a new Blog Post before redirecting to /posts
    function processPost(imageUrl) {
      req.body.featureImage = imageUrl;

      blogData
        .addPost(req.body)
        .then((post) => {
          res.redirect("/posts");
        })
        .catch((err) => {
          res.status(500).send(err);
        });
    }
  }
);

app.get("/login", (req, res) => {
  res.render("login");
});

app.get("/register", (req, res) => {
  res.render("register");
});

app.post("/register", (req, res) => {
  authData
    .registerUser(req.body)
    .then((user) => {
      res.render("register", { successMessage: "User created" });
    })
    .catch((err) => {
      res.render("register", {
        errorMessage: err,
        userName: req.body.userName,
      });
    });
});

app.post("/login", (req, res) => {
  req.body.userAgent = req.get("User-Agent");

  authData
    .checkUser(req.body)
    .then((user) => {
      req.session.user = {
        userName: user.userName,
        email: user.email,
        loginHistory: user.loginHistory,
      };

      res.redirect("/posts");
    })
    .catch((err) => {
      res.render("login", { errorMessage: err, userName: req.body.userName });
    });
});

app.get("/logout", (req, res) => {
  req.session.reset();
  res.redirect("/");
});

app.get("/userHistory", authData.ensureLogin, (req, res) => {
  res.render("userHistory");
});

// Any other routes will return a custom message with an HTTP status code
app.use(function (req, res, next) {
  res.status(404).render("404");
});

blogData
  .initialize()
  .then(authData.initialize)
  .then(() => {
    // The server must output: "Express http server listening on port" to the
    // console, where port is the port the server is currently listening on
    app.listen(HTTP_PORT, () => {
      console.log("Express http server listening on " + HTTP_PORT);
    });
  })
  .catch((err) => {
    console.error(err);
  });
