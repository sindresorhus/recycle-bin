#include <stdio.h>
#include <windows.h>
#include <assert.h>

int wmain(int argc, wchar_t **argv) {
	if (argc == 2) {
		if (wcscmp(argv[1], L"--version") == 0) {
			puts("1.0.1");
			return 0;
		}

		if (wcscmp(argv[1], L"--help") == 0) {
			puts("\n  Move files and folders to the recycle bin\n\n  Usage: recycle-bin <path> [...]\n\n  Created by Sindre Sorhus");
			return 0;
		}
	}

	if (argc == 1) {
		puts("Specify at least one path");
		return 1;
	}

	int i;
	size_t len = argc;

	for (i = 1; i < argc; i++) {
		len += wcslen(argv[i]);
	}

	wchar_t *from = malloc(len * sizeof(wchar_t));

	int pos = 0;

	for (i = 1; i < argc; i++) {
		wcscpy(&from[pos], argv[i]);
		pos += wcslen(argv[i]) + 1;
	}

	from[pos] = '\0';

	assert(++pos == len && "position/length mismatch");

	SHFILEOPSTRUCTW op;

	op.hwnd = NULL;
	op.wFunc = FO_DELETE;
	op.pFrom = from;
	op.pTo = NULL;
	op.fFlags = FOF_ALLOWUNDO | FOF_NO_UI;

	int ret = SHFileOperationW(&op);

	free(from);

	return ret;
}
