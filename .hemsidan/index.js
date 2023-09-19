const http = require('http');
const fs = require('fs');

const server = http.createServer((req, res) => {
  fs.readFile('pirat_hobbyer.html', (err, data) => {
    if (err) {
      res.writeHead(404);
      res.end('File not found');
    } else {
      res.writeHead(200, {'Content-Type': 'text/html'});
      res.end(data);
    }
  });
});

const port = process.env.PORT || 3000;
server.listen(port, () => {
  console.log(`Server kører på http://localhost:${port}/`);
});
