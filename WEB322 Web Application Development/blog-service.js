const Sequelize = require("sequelize");
const { gte } = Sequelize.Op;

// set up sequelize to point to our postgres database
var sequelize = new Sequelize(
  "qpxtjrmr",
  "qpxtjrmr",
  "2omtPOfumdSJPgLoTyQ2yG2r6OR2pYcC",
  {
    host: "isilo.db.elephantsql.com",
    dialect: "postgres",
    port: 5432,
    dialectOptions: {
      ssl: { rejectUnauthorized: false },
    },
    query: { raw: true },
  }
);

// Define a "Post" model
var Post = sequelize.define("Post", {
  body: Sequelize.TEXT,
  title: Sequelize.STRING,
  postDate: Sequelize.DATE,
  featureImage: Sequelize.STRING,
  published: Sequelize.BOOLEAN,
});

// Define a "Category" model
var Category = sequelize.define("Category", {
  category: Sequelize.STRING,
});

// Define the relationship between Post and Category models
Post.belongsTo(Category, { foreignKey: "category" });

function initialize() {
  return new Promise((resolve, reject) => {
    sequelize
      .sync()
      .then(() => {
        resolve("Database sync successful");
      })
      .catch((error) => {
        reject("Unable to sync the database");
      });
  });
}

function getAllPosts() {
  return new Promise((resolve, reject) => {
    Post.findAll()
      .then((posts) => {
        if (posts && posts.length > 0) {
          resolve(posts);
        } else {
          reject("No results returned");
        }
      })
      .catch((error) => {
        reject("Error fetching posts");
      });
  });
}

function getPublishedPosts() {
  return new Promise((resolve, reject) => {
    Post.findAll({
      where: {
        published: true,
      },
    })
      .then((posts) => {
        if (posts && posts.length > 0) {
          resolve(posts);
        } else {
          reject("No results returned");
        }
      })
      .catch((error) => {
        reject("Error fetching posts");
      });
  });
}

function getCategories() {
  return new Promise((resolve, reject) => {
    Category.findAll()
      .then((categories) => {
        if (categories && categories.length > 0) {
          resolve(categories);
        } else {
          reject("No results returned");
        }
      })
      .catch((error) => {
        reject("Error fetching categories");
      });
  });
}

function addPost(postData) {
  return new Promise((resolve, reject) => {
    // Ensure published property is set properly
    postData.published = postData.published ? true : false;

    // Replace empty values with null
    for (let key in postData) {
      if (postData[key] === "") {
        postData[key] = null;
      }
    }

    // Assign current date to postDate
    postData.postDate = new Date();

    // Invoke Post.create() function
    Post.create(postData)
      .then(() => {
        resolve("Post created successfully");
      })
      .catch((error) => {
        reject("Unable to create post");
      });
  });
}

function addCategory(categoryData) {
  return new Promise((resolve, reject) => {
    // Replace empty values with null
    for (let key in categoryData) {
      if (categoryData[key] === "") {
        categoryData[key] = null;
      }
    }

    // Invoke Category.create() function
    Category.create(categoryData)
      .then(() => {
        resolve("Category created successfully");
      })
      .catch((error) => {
        reject("Unable to create category");
      });
  });
}

function deleteCategoryById(id) {
  return new Promise((resolve, reject) => {
    Category.destroy({ where: { id } })
      .then((rowsDeleted) => {
        if (rowsDeleted > 0) {
          // If the category was deleted, resolve the promise
          resolve("Category deleted successfully");
        } else {
          // If no category was deleted, reject the promise
          reject("Category not found");
        }
      })
      .catch((error) => {
        // If there was an error, reject the promise with a meaningful message
        reject("Error deleting category");
      });
  });
}

function deletePostById(id) {
  return new Promise((resolve, reject) => {
    Post.destroy({ where: { id } })
      .then((rowsDeleted) => {
        if (rowsDeleted > 0) {
          // If the post was deleted, resolve the promise
          resolve("Post deleted successfully");
        } else {
          // If no post was deleted, reject the promise
          reject("Post not found");
        }
      })
      .catch((error) => {
        // If there was an error, reject the promise with a meaningful message
        reject("Error deleting post");
      });
  });
}

function getPostsByCategory(category) {
  return new Promise((resolve, reject) => {
    Post.findAll({
      where: {
        category: category,
      },
    })
      .then((posts) => {
        if (posts && posts.length > 0) {
          resolve(posts);
        } else {
          reject("No results returned");
        }
      })
      .catch((error) => {
        reject("Error fetching posts");
      });
  });
}

function getPostsByMinDate(minDateStr) {
  return new Promise((resolve, reject) => {
    Post.findAll({
      where: {
        postDate: {
          [gte]: new Date(minDateStr),
        },
      },
    })
      .then((posts) => {
        if (posts && posts.length > 0) {
          resolve(posts);
        } else {
          reject("No results returned");
        }
      })
      .catch((error) => {
        reject("Error fetching posts");
      });
  });
}

function getPostById(id) {
  return new Promise((resolve, reject) => {
    Post.findAll({
      where: {
        id: id,
      },
    })
      .then((posts) => {
        if (posts && posts.length > 0) {
          resolve(posts[0]);
        } else {
          reject("No results returned");
        }
      })
      .catch((error) => {
        reject("Error fetching posts");
      });
  });
}

function getPublishedPostsByCategory(category) {
  return new Promise((resolve, reject) => {
    Post.findAll({
      where: {
        published: true,
        category: category,
      },
    })
      .then((posts) => {
        if (posts && posts.length > 0) {
          resolve(posts);
        } else {
          reject("No results returned");
        }
      })
      .catch((error) => {
        reject("Error fetching posts");
      });
  });
}

module.exports = {
  initialize,
  getAllPosts,
  getPublishedPosts,
  getCategories,
  addPost,
  addCategory,
  deleteCategoryById,
  deletePostById,
  getPostsByCategory,
  getPostsByMinDate,
  getPostById,
  getPublishedPostsByCategory,
};
