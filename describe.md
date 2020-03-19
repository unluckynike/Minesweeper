  function MessageBox(hWnd: HWND; Text, Caption: PChar; Type: Word): Integer;  
　hWnd：对话框父窗口句柄，对话框显示在Delphi窗体内，可使用窗体的Handle属性，否则可用0，使其直接作为桌面窗口的子窗口。  
　Text：欲显示的信息字符串。  
　Caption：对话框标题字符串。  
　Type：对话框类型常量。  
　该函数的返回值为整数，用于对话框按钮的识别。  
　2、类型常量  
　对话框的类型常量可由按钮组合、缺省按钮、显示图标、运行模式四种常量组合而成。  
　（1）按钮组合常量  
　MB_OK = $00000000;　　　　　　　　　//一个确定按钮  
　MB_OKCANCEL = $00000001;　　　　　　//一个确定按钮，一个取消按钮  
　MB_ABORTRETRYIGNORE = $00000002;　　//一个异常终止按钮，一个重试按钮，一个忽略按钮  
　MB_YESNOCANCEL = $00000003;　　　　 //一个是按钮，一个否按钮，一个取消按钮  
　MB_YESNO = $00000004;　　　　　　　 //一个是按钮，一个否按钮  
　MB_RETRYCANCEL = $00000005;　　　　 //一个重试按钮，一个取消按钮  
　（2）缺省按钮常量
　MB_DEFBUTTON1 = $00000000;　　　　　//第一个按钮为缺省按钮  
　MB_DEFBUTTON2 = $00000100;　　　　　//第二个按钮为缺省按钮  
　MB_DEFBUTTON3 = $00000200;　　　　　//第三个按钮为缺省按钮  
　MB_DEFBUTTON4 = $00000300;　　　　　//第四个按钮为缺省按钮  
　（3）图标常量
　MB_ICONHAND = $00000010;　　　　　　　 //“×”号图标  
　MB_ICONQUESTION = $00000020;　　　　　 //“？”号图标  
　MB_ICONEXCLAMATION = $00000030;　　　　//“！”号图标  
　MB_ICONASTERISK = $00000040;　　　　　 //“i”图标  
　MB_USERICON = $00000080;　　　　　　　 //用户图标  
　MB_ICONWARNING = MB_ICONEXCLAMATION;　 //“！”号图标  
　MB_ICONERROR = MB_ICONHAND;　　　　　　//“×”号图标  
　MB_ICONINFORMATION = MB_ICONASTERISK;　//“i”图标  
　MB_ICONSTOP = MB_ICONHAND;　　　　　　 //“×”号图标  
　（4）运行模式常量  
　MB_APPLMODAL = $00000000;　　　　//应用程序模式，在未结束对话框前也能切换到另一应用程序  
　MB_SYSTEMMODAL = $00001000;　　　//系统模式，必须结束对话框后，才能做其他操作  
　MB_TASKMODAL = $00002000;　　　　//任务模式，在未结束对话框前也能切换到另一应用程序  
　MB_HELP = $00004000;　　　　　　 //Help Button  
　3、函数返回值  
　0　　　　　　　　　　　 //对话框建立失败  
　IDOK = 1　　　　　　　　//按确定按钮  
　IDCANCEL = 2　　　　　　//按取消按钮  
　IDABOUT = 3　　　　　　 //按异常终止按钮  
　IDRETRY = 4　　　　　　 //按重试按钮  
　IDIGNORE = 5　　　　　　//按忽略按钮  
　IDYES = 6　　　　　　　 //按是按钮  
　IDNO = 7　　　　　　　　//按否按钮  
二 用法  

1. MessageBox("这是一个最简单的消息框！");  
2. MessageBox("这是一个有标题的消息框！","标题");  
3. MessageBox("这是一个确定 取消的消息框！","标题", MB_OKCANCEL );  
4. MessageBox("这是一个警告的消息框！","标题", MB_ICONEXCLAMATION );  
5. MessageBox("这是一个两种属性的消息框！","标题",MB_ICONEXCLAMATION|MB_OKCANCEL );  
6. if(MessageBox("一种常用的应用","标题" ,MB_ICONEXCLAMATION|MB_OKCANCEL)==IDCANCEL)  
		 return;
注意：  
以上消息框的用法是在CWnd的子类中的应用，如果不是，则要MessageBox(NULL,"ddd","ddd",MB_OK);   
或MessageBox(hWnd,"ddd","ddd",MB_OK); hWnd为某窗口的句柄，或者直接用AfxMessageBox。  

二、在MessageBox中显示变量的值  

	 CString string;

	  string.format("%d%s",m_age, m_address); //将变量组装到字符串中

	   MessageBox(string,"消息框标题",消息框类型);
