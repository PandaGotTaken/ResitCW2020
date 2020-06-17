#include "editor.h"

int main()
{
	Editor editorApp;

	editorApp.init();
	editorApp.run();
	editorApp.shutdown();

	return 0;
}