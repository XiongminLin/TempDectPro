/*2014年4月15日*/
Q:无法同时打开多个Imager界面程序。
A：
1. 将桌面的PI Connect，复制一个附本。 然后装名称改为：PI Connect-1 ； PI Connect-2
2. 在PI Connect-1图标上点右键按“属性”，将有弹出窗口。
3. 在“快捷方式”下有“目标(T)”，请将路径后增加“ /name=camera1”; 例如："C:\Program Files (x86)\Optris GmbH\PI Connect\Imager.exe" /name=camera1 
4. 在PI Connect-2图标按2.3步骤操作，在路径后增加“ /name=camera2”; 例如："C:\Program Files (x86)\Optris GmbH\PI Connect\Imager.exe" /name=camera2 
5. 分别打开PI Connect-1；PI Connect-2将会出来2个界面。 


/*2014年4月16日*/
Q：提示找不到Graph
A：路径 “ /name=camera1”的最好不要有空格。

Q：打开提示库文件不对。
A：旧版本的库文件还残留在C:\Windows\System32里面，将其清理删除即可。

Q：厂家自带的Start MultiIPC2.exe 程序或是自己写的程序无法链接到Imager.exe上，只有将上面添加的“ /name=camera1”路径去掉才行。
A:链接不上程序是因为没有将Instance name的值设置为camera1和camera2，填写上去就可以正常工作了。