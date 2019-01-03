var express = require('express')
var multer  = require('multer')
var app = express()

/*
const storage =  multer.diskStorage({
  destination: './uploads/',
  filename: function(req,file,cb){
    cb(null, file.originalname);
  }
});
const upload = multer({ storage: storage });
*/
const upload = multer({ dest: 'uploads/' })

app.post('/api/image', upload.single('image'), function (req, res, next) {
  console.log("/api/image");
  console.log(req.body);
  console.log(req.file);
  res.send({"status":true,"error":""});
});

var server = app.listen(8080, "192.168.100.140", function () {
    var host = server.address().address;
    var port = server.address().port;

    console.log('Example app listening at http://%s:%s', host, port);
});
server.timeout = 15 * 60 * 1000;