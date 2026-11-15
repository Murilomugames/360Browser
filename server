
"""Servidor inicial do 360Browser."""
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from urllib.parse import urlparse, parse_qs
from urllib.request import Request, urlopen
from html.parser import HTMLParser
import re

HOST = "0.0.0.0"
PORT = 8765

ALLOWED_DOMAINS = {
    "wikipedia.org",
    "duckduckgo.com",
    "github.com",
}

class TextExtractor(HTMLParser):
    def __init__(self):
        super().__init__()
        self.parts = []
        self.skip = 0

    def handle_starttag(self, tag, attrs):
        if tag in ("script", "style", "svg", "iframe"):
            self.skip += 1
        elif not self.skip and tag in ("p", "div", "h1", "h2", "h3", "br"):
            self.parts.append("\n")

    def handle_endtag(self, tag):
        if tag in ("script", "style", "svg", "iframe") and self.skip:
            self.skip -= 1

    def handle_data(self, data):
        if not self.skip and data.strip():
            self.parts.append(data.strip())

def allowed(host):
    host = (host or "").lower()
    return any(host == d or host.endswith("." + d)
               for d in ALLOWED_DOMAINS)

def get_page(url):
    parsed = urlparse(url)

    if parsed.scheme not in ("http", "https"):
        raise ValueError("Use HTTP ou HTTPS.")

    if not allowed(parsed.hostname):
        raise ValueError("Site ainda não permitido.")

    request = Request(
        url,
        headers={"User-Agent": "360Browser/0.1"}
    )

    with urlopen(request, timeout=8) as response:
        if response.status != 200:
            raise ValueError("Erro ao carregar página.")

        content_type = response.headers.get("Content-Type", "")
        if "text/html" not in content_type:
            raise ValueError("Somente páginas HTML.")

        data = response.read(512 * 1024)
        html = data.decode("utf-8", errors="replace")

    parser = TextExtractor()
    parser.feed(html)

    return re.sub(r"\n{3,}", "\n\n", "\n".join(parser.parts))

class Handler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path.startswith("/browse?"):
            url = parse_qs(urlparse(self.path).query).get("url", [""])[0]

            try:
                result = get_page(url)
                self.send_result(200, result)
            except Exception as error:
                self.send_result(400, str(error))
        else:
            self.send_result(200, "360Browser Proxy 0.1")

    def send_result(self, status, text):
        data = text.encode("utf-8", errors="replace")
        self.send_response(status)
        self.send_header("Content-Type", "text/plain; charset=utf-8")
        self.send_header("Content-Length", str(len(data)))
        self.end_headers()
        self.wfile.write(data)

if __name__ == "__main__":
    print("360Browser iniciado na porta", PORT)
    ThreadingHTTPServer((HOST, PORT), Handler).serve_forever()
