var http = require('http');
var fs = require('fs');

var file = fs.readFileSync('index.htm', 'utf8');

    var server = http.createServer(function(request, response){
      if (request.method == 'POST') {
        var body = '';

        request.on('data', function (data) {
            body += data;

            // Too much POST data, kill the connection!
            // 1e6 === 1 * Math.pow(10, 6) === 1 * 1000000 ~~~ 1MB
            if (body.length > 1e6)
                request.connection.destroy();
        });
        request.on('end', function () {
           var post = body
           console.log(post);
       });
     }
        response.writeHead(200, {'Content-Type': 'text/html'});
        response.write(file);
        response.end();
    });

    server.listen(8001);
