var http = require('http');
var fs = require('fs');

var file = fs.readFileSync('index.htm', 'utf8');

    var server = http.createServer(function(request, response){
        response.writeHead(200, {'Content-Type': 'text/html'});
        response.write(file);
        response.end();
    });

    server.listen(8001);
