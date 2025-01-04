#include <Arduino.h>

// String html_Content = R"(
// <!DOCTYPE html>
// <html>
// <head>
//   <meta charset="utf-8">
//   <title>WiFi Settings</title>
// </head>
// <body>
//   <h1>WiFi Settings</h1>
//   <form action="/setwifi" method="post">
//     <label for="wifiname">WiFi Name:</label>
//     <input type="text" id="wifiname" name="wifiname"><br>
//     <label for="wifipassword">WiFi Password:</label>
//     <input type="text" id="wifipassword" name="wifipassword"><br>
//     <input type="submit" value="Save">
//   </form>
//   <br>
//   <a href="/wifilist"><button>Go to WiFi List</button></a>
//   <br>
//   <h2>Current WiFi Info:</h2>
//   <p>%WIFIINFO%</p>  <!-- 用一个占位符插入WiFi信息 -->
// </body>
// </html>
// )";

String html_Content = R"(
<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <title>WiFi Info</title>
</head>
<body>
  <h3>WiFi Settings</h3>
  <form action="/setwifi" method="post">
    <label for="wifiname">WiFi Name:</label>
    <input type="text" id="wifiname" name="wifiname"><br>
    <label for="wifipassword">WiFi Password:</label>
    <input type="text" id="wifipassword" name="wifipassword"><br>
    <input type="submit" value="Save">
  </form>
  <br>
  <h3>Available WiFi Networks:</h3>
  {{wifiInfo}}
</body>
</html>
)";