#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char const *argv[])
{
	int sock0;
	struct sockaddr_in addr;
	struct sockaddr_in client;
	int len;
	int sock;

	/* ソケットの作成 */
	sock0 = socket(AF_INET, SOCK_STREAM, 0);

	/* ソケットの設定 */
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.s_addr = INADDR_ANY;
	bind(sock0, (struct sockaddr *)&addr, sizeof(addr));

	/* TCPクライアントからの接続要求を待てる状態にする */
	listen(sock0, 5);

	/* TCPクライアントからの接続要求を受け付ける */
	/* 5文字送信 */
	/* TCPセッションの終了 */
	/* listenするsocketの終了 */

	printf("Hello World\n");

	return 0;
}