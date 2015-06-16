#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

static const int PORT = 12345;
static const char* IP = "127.0.0.1";

int main(int argc, char const *argv[])
{
	struct sockaddr_in server;
	int sock;
	char buf[32];
	int n;

	/* ソケットの作成 */
	sock = socket(AF_INET, SOCK_STREAM, 0);

	/* 接続先指定用構造体の準備 */
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	inet_pton(AF_INET, IP, &server.sin_addr.s_addr); // IPv4/IPv6 アドレスをテキスト形式からバイナリ形式に変換する

	/* サーバに接続 */
	connect(sock, (struct sockaddr *)&server, sizeof(server));

	/* サーバからデータを受信 */
	memset(buf, 0, sizeof(buf)); // ある一定のバイトでメモリー領域を埋める。
	n = read(sock, buf, sizeof(buf)); // ファイルディスクリプターから読み込む

	/* 出力 */
	printf("%d, %s\n", n, buf);

	/* ソケットの終了 */
	close(sock);

	return 0;
}