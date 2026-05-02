#include <fcgiapp.h>

int main(void) {
  FCGX_Init();
  FCGX_Request req;
  FCGX_InitRequest(&req, 0, 0);

  while (FCGX_Accept_r(&req) == 0) {
    FCGX_FPrintF(req.out,
      "Content-Type: text/html\r\n\r\n"
      "<html><body><h1>Hello, World!</h1></body></html>\n"
    );
    FCGX_Finish_r(&req);
  }
  return 0;
}
