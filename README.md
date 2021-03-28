# wearlevel
wearlevel project that checks 1) how long OS has been running, 2) how many bytes read and written during uptime.

Note: 1) Project created in Visual Studio Code <br/>
2) built using MinGW on Windows <br/>
<p>
Here is a helpful link to getting MinGW set up with VSCode: <a href="https://code.visualstudio.com/docs/languages/cpp">https://code.visualstudio.com/docs/languages/cpp</a><br/>
That link also contains links to where you can get MinGW.
</p>

<p>
Windows header file info: <a href="https://docs.microsoft.com/en-us/windows/win32/winprog/using-the-windows-headers">https://docs.microsoft.com/en-us/windows/win32/winprog/using-the-windows-headers</a>
</p>
<p>
tasks.json contains the VSCode compiler options. Two very important ones I added :
<ul>
<li>-D_WIN32_WINNT=0x0600  // compiles toward newer platform enables support for 64 bit API calls (GetTickCount64())</li>
<li>-static // builds exe with statically linked libraries so you can deploy just .exe and it'll run on other people's systems.</li>
</ul>
</p>
