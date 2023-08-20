const mongoose = require("mongoose");
const bcrypt = require("bcryptjs");

var Schema = mongoose.Schema;

var userSchema = new Schema({
  userName: {
    type: String,
    unique: true,
  },
  password: String,
  email: String,
  loginHistory: [
    {
      dateTime: Date,
      userAgent: String,
    },
  ],
  country: String,
});
module.exports = mongoose.model("User", userSchema);

let User;

module.exports.initialize = function () {
  return new Promise(function (resolve, reject) {
    let db = mongoose.createConnection(
      "mongodb+srv://sang:shjeon5@sangscluster.0iwgfz4.mongodb.net/WEB322_Assignment_6"
    );

    db.on("error", (err) => {
      reject(err);
    });
    db.once("open", () => {
      User = db.model("users", userSchema);
      resolve();
    });
  });
};

module.exports.registerUser = function (userData) {
  return new Promise(function (resolve, reject) {
    if (userData.password !== userData.password2) {
      reject("Passwords do not match");
    } else {
      bcrypt
        .hash(userData.password, 10)
        .then((hash) => {
          userData.password = hash;
          let newUser = new User(userData);

          newUser.save((err) => {
            if (err) {
              if (err.code === 11000) {
                reject("User Name already taken");
              } else {
                reject(`There was an error creating the user: ${err}`);
              }
            } else {
              resolve();
            }
          });
        })
        .catch((err) => {
          reject("There was an error encrypting the password");
        });
    }
  });
};

module.exports.checkUser = function (userData) {
  return new Promise(function (resolve, reject) {
    User.find({ userName: userData.userName }, (err, users) => {
      if (err) {
        reject(`Unable to find user: ${userData.userName}`);
      } else {
        if (users.length === 0) {
          reject(`Unable to find user: ${userData.userName}`);
        } else {
          bcrypt
            .compare(userData.password, users[0].password)
            .then((result) => {
              if (result) {
                let loginData = {
                  dateTime: new Date().toString(),
                  userAgent: userData.userAgent,
                };

                users[0].loginHistory.push(loginData);

                User.updateOne(
                  { userName: users[0].userName },
                  { $set: { loginHistory: users[0].loginHistory } },
                  (err) => {
                    if (err) {
                      reject(`There was an error verifying the user: ${err}`);
                    } else {
                      resolve(users[0]);
                    }
                  }
                );
              } else {
                reject(`Incorrect Password for user: ${userData.userName}`);
              }
            });
        }
      }
    });
  });
};

module.exports.ensureLogin = function (req, res, next) {
  if (!req.session.user) {
    res.redirect("/login");
  } else {
    next();
  }
};
