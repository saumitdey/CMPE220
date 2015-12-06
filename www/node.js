/**
 * Created by Sourav on 11/6/2015.
 */
var http = require('http');
var fs = require('fs');

var index = fs.readFileSync('index.html');
http.createServer(function(req,res){
    res.writeHead(200, {'Content-Type': 'text/html'});
    res.end(index);
}).listen(8888);
console.log('Server running at http://localhost:8888/');