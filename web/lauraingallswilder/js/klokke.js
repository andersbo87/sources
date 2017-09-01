// JScript File
/*By George Chiang (JK's JavaScript tutorial)
        http://www.javascriptkit.com
        Credit MUST stay intact for use*/
        var dn
        c1=new Image(); c1.src="images/c1.gif"
        c2=new Image(); c2.src="images/c2.gif"
        c3=new Image(); c3.src="images/c3.gif"
        c4=new Image(); c4.src="images/c4.gif"
        c5=new Image(); c5.src="images/c5.gif"
        c6=new Image(); c6.src="images/c6.gif"
        c7=new Image(); c7.src="images/c7.gif"
        c8=new Image(); c8.src="images/c8.gif"
        c9=new Image(); c9.src="images/c9.gif"
        c0=new Image(); c0.src="images/c0.gif"
        cb=new Image(); cb.src="images/cb.gif"
        cam=new Image(); cam.src="images/cam.gif"
        cpm=new Image(); cpm.src="images/cpm.gif"
        colon=new Image(); colon.src="images/colon.gif"
        function extract(h,m,s,type)
        {
            if (!document.images)
                return
            if (h<=9)
            {
                document.images.a.src="images/c0.gif"
                document.images.b.src=eval("c"+h+".src")
            }
            else 
            {
                document.images.a.src=eval("c"+Math.floor(h/10)+".src")
                document.images.b.src=eval("c"+(h%10)+".src")
            }
            if (m<=9)
            {
                document.images.d.src="images/c0.gif"
                document.images.e.src=eval("c"+m+".src")
            }
            else 
            {
                document.images.d.src=eval("c"+Math.floor(m/10)+".src")
                document.images.e.src=eval("c"+(m%10)+".src")
            }
            if (s<=9)
            {
                document.g.src="images/c0.gif"
                document.images.h.src=eval("c"+s+".src")
            }
            else 
            {
                document.images.g.src=eval("c"+Math.floor(s/10)+".src")
                document.images.h.src=eval("c"+(s%10)+".src")
            }

        }
        function show3()
        {
            if (!document.images)
                return
            var Digital=new Date()
            var hours=Digital.getHours()
            var minutes=Digital.getMinutes()
            var seconds=Digital.getSeconds()

            if ((hours>=12)&&(minutes>=1)||(hours>=13))
            {
                hours=hours-0
            }
            if (hours==12)
                hours=12
            extract(hours,minutes,seconds,dn)
            setTimeout("show3()",1000)
        }
