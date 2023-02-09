// 230208_gd_C.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <windows.h>

#define BUFSIZE 4096

int main()
{
  HANDLE hPipe;
  LPCWSTR lpvMessage = TEXT("Default message from client");
  TCHAR chBuf[BUFSIZE];
  BOOL fSuccess;
  DWORD cbRead, cbWritten, dwMode;
  LPCWSTR lpszPipename = TEXT("\\\\.\\pipe\\mynamepipe");

  /*if (argc > 1)
	lpvMessage = argv[1];*/

  // Try to open a named pipe; wait for it, if necessary.   

  while (1)
  {
	hPipe = CreateFile(
	  lpszPipename,   // pipe name   
	  GENERIC_READ |  // read and write access   
	  GENERIC_WRITE,
	  0,              // no sharing   
	  NULL,           // default security attributes  
	  OPEN_EXISTING,  // opens existing pipe   
	  0,              // default attributes   
	  NULL);          // no template file   

  // Break if the pipe handle is valid.   

	if (hPipe != INVALID_HANDLE_VALUE)
	  break;

	// Exit if an error other than ERROR_PIPE_BUSY occurs.   

	if (GetLastError() != ERROR_PIPE_BUSY)
	{
	  printf("Could not open pipe");
	  return 0;
	}

	// All pipe instances are busy, so wait for 20 seconds.   

	if (!WaitNamedPipe(lpszPipename, 20000))
	{
	  printf("Could not open pipe");
	  return 0;
	}
  }

  // The pipe connected; change to message-read mode.   

  dwMode = PIPE_READMODE_MESSAGE;
  fSuccess = SetNamedPipeHandleState(
	hPipe,    // pipe handle   
	&dwMode,  // new pipe mode   
	NULL,     // don't set maximum bytes   
	NULL);    // don't set maximum time   
  if (!fSuccess)
  {
	printf("SetNamedPipeHandleState failed");
	return 0;
  }

  // Send a message to the pipe server.   

  fSuccess = WriteFile(
	hPipe,                  // pipe handle   
	lpvMessage,             // message   
	(lstrlen(lpvMessage) + 1) * sizeof(TCHAR), // message length   
	&cbWritten,             // bytes written   
	NULL);                  // not overlapped   
  if (!fSuccess)
  {
	printf("WriteFile failed");
	return 0;
  }

  do
  {
	// Read from the pipe.   

	fSuccess = ReadFile(
	  hPipe,    // pipe handle   
	  chBuf,    // buffer to receive reply   
	  BUFSIZE * sizeof(TCHAR),  // size of buffer   
	  &cbRead,  // number of bytes read   
	  NULL);    // not overlapped   

	if (!fSuccess && GetLastError() != ERROR_MORE_DATA)
	  break;

	//_tprintf(TEXT("%s\n"), chBuf);
  } while (!fSuccess);  // repeat loop if ERROR_MORE_DATA   

  //getch();

  CloseHandle(hPipe);

  return 0;
}

