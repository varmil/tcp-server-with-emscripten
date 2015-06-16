#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

static const int PORT = 12345;

int main(int argc, char const *argv[])
{
	int sock0;
	struct sockaddr_in addr;
	struct sockaddr_in client;
	int len;
	int sock;

	/* リスニングソケットの作成(domain: IPv4, type: TCP/IP, protocol: 自動設定) */
	sock0 = socket(AF_INET, SOCK_STREAM, 0); // ファイルディスクリプタが返り値。

	/* リスニングソケットの設定（ポートをbind） */
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = INADDR_ANY;
	bind(sock0, (struct sockaddr *)&addr, sizeof(addr));

	/* TCPクライアントからの接続要求を待てる状態にする */
	listen(sock0, 5); // コネクションの確立時にクライアントからの接続要求を格納するキューをサーバ側で作る。

	/* TCPクライアントからの接続要求を受け付ける。実際の送受信は、返り値の接続済ソケットを使って行う */
	/* リスニングソケットを使って再度acceptを呼び出してやると、別の接続待ちに入る */
	/* listenはリスニングソケットに対して最初の1回しか行わないが、acceptは何度も行う */
	while(true) {
		printf("Waiting... \n");

		sock = accept(sock0, (struct sockaddr *)&client, (socklen_t *)sizeof(client)); // 処理を中断して受付開始。クライアントからの接続要求に合わせて、listen()でキューイングしたソケットを取得
		/* 5文字送信 */
		write(sock, "HELLO", 5);

		printf("Accepted \n");
	}


	/* TCPセッションの終了 */
	close(sock);

	/* リスニングソケットの終了 */
	close(sock0);

	return 0;
}