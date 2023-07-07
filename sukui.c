#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

static void header(void);
static void body(void);

int
main(int argc, char *argv[])
{
	header();
	body();

	return 0;
}

static void
header(void)
{
	const char *headerFormat =
		"HTTP/1.1 200 There is no sukui\r\n"
		"Content-Type: text/html; charset=utf-8\r\n"
		"Cache-Control: no-cache, no-store\r\n"
		;

	printf("%s", headerFormat);
	printf("\r\n");
}

static void
body(void)
{
	const char *bodyHead =
		"<head>"
		"<meta charset='utf-8'>"
		"<title>お前の救いメーカー</title>"
		"<style>"
		"body { position: relative; overflow: hidden; }"
		"</style>"
		"</head>"
		;
	const char *bodyBody =
		"<body>"
		"%s"
		"</body>"
		;
	const char *bodyScript =
		"<script>"
		"'use strict';"
		"let h = 0;\n"
		"function main() {\n"
		"	document.body.style.background = `hsl(${h++}, 100%, 50%)`;\n"
		"	const div = document.createElement('div');\n"
		"	div.style.position = 'absolute';\n"
		"	div.style.display = 'inline-block';\n"
		"	div.style.fontSize = `${Math.random() * 64}px`;\n"
		"	div.style.color = `hsl(${Math.random() * 360}, ${Math.random() * 100}%, ${Math.random() * 100}%)`;\n"
		"	div.style.wordBreak = 'keep-all';\n"
		"	div.textContent = '救いはあります';\n"
		"	div.style.top = `${Math.random() * window.innerHeight * 2 - window.innerHeight}px`;\n"
		"	div.style.left = `${Math.random() * window.innerWidth * 2 - window.innerWidth}px`;\n"
		"	div.style.transform = `rotate(${Math.PI * (2 * Math.random() - 1)}rad)`;\n"
		"	document.body.appendChild(div);\n"
		"	window.requestAnimationFrame(main);\n"
		"}"
		"document.body.style.background = `hsl(${h}, 100%, 50%)`;\n"
		"setTimeout(() => main(), 1000);\n"
		"</script>"
		;
	int k;
	char *str;

	srand((unsigned)time(NULL) + (unsigned)getpid());
	k = rand() % 10000;
	if (k > 9900)
		str = "救いはあります";
	else if (k > 9000)
		str = "救いはありました";
	else if (k > 5000)
		str = "救いはありません";
	else if (k > 1000)
		str = "救いはないです";
	else
		str = "";

	printf("<!DOCTYPE html>");
	printf("<html>");
	printf("%s", bodyHead);
	printf(bodyBody, str);
	if (k > 9900)
		printf("%s", bodyScript);
	printf("</html>");
}
