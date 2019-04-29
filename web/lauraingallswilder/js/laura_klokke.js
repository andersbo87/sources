// JScript File
/*By George Chiang (JK's JavaScript tutorial)
        http://www.javascriptkit.com
        Credit MUST stay intact for use*/
        var dn, imgPath = "./images/";
        c1=new Image(); c1.src= imgPath + "c1.gif"
        c2=new Image(); c2.src= imgPath + "c2.gif"
        c3=new Image(); c3.src= imgPath + "c3.gif"
        c4=new Image(); c4.src= imgPath + "c4.gif"
        c5=new Image(); c5.src= imgPath + "c5.gif"
        c6=new Image(); c6.src= imgPath + "c6.gif"
        c7=new Image(); c7.src= imgPath + "c7.gif"
        c8=new Image(); c8.src= imgPath + "c8.gif"
        c9=new Image(); c9.src= imgPath + "c9.gif"
        c0=new Image(); c0.src= imgPath + "c0.gif"
        cb=new Image(); cb.src= imgPath + "cb.gif"
        cam=new Image(); cam.src= imgPath + "cam.gif"
        cpm=new Image(); cpm.src= imgPath + "cpm.gif"
        colon=new Image(); colon.src= imgPath + "colon.gif"
        function extract(h,m,s,type)
        {
            if (!document.images)
                return
            if (h<=9)
            {
                document.images.a.src= imgPath + "c0.gif"
                document.images.b.src=eval("c"+h+".src")
            }
            else 
            {
                document.images.a.src=eval("c"+Math.floor(h/10)+".src")
                document.images.b.src=eval("c"+(h%10)+".src")
            }
            if (m<=9)
            {
                document.images.d.src= imgPath + "c0.gif"
                document.images.e.src=eval("c"+m+".src")
            }
            else 
            {
                document.images.d.src=eval("c"+Math.floor(m/10)+".src")
                document.images.e.src=eval("c"+(m%10)+".src")
            }
            if (s<=9)
            {
                document.g.src= imgPath + "c0.gif"
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
