<script type="text/javascript">
      
    var l=document.location + "";
    l=l.replace(/%20/g," ");
    var index=l.indexOf('?t=');
    if(index==-1) document.location=l + "?t=Hello";
  
    var pixels=new Array();
    var canv=$('canv');
    var ctx=canv.getContext('2d');
    var wordCanv=$('wordCanv');
    var wordCtx=wordCanv.getContext('2d');
    var mx=-1;
    var my=-1;
    var words="";
    var txt=new Array();
    var cw=0;
    var ch=0;
    var resolution=1;
    var n=0;
    var timerRunning=false;
    var resHalfFloor=0;
    var resHalfCeil=0;
    
    function canv_mousemove(evt)
    {
      mx=evt.clientX-canv.offsetLeft;
      my=evt.clientY-canv.offsetTop;
    }
    
    function Pixel(homeX,homeY)
    {
      this.homeX=homeX;
      this.homeY=homeY;
      
      this.x=Math.random()*cw;
      this.y=Math.random()*ch;
      
      //tmp
      this.xVelocity=Math.random()*10-5;
      this.yVelocity=Math.random()*10-5;
    }
    Pixel.prototype.move=function()
    {
      var homeDX=this.homeX-this.x;
      var homeDY=this.homeY-this.y;
      var homeDistance=Math.sqrt(Math.pow(homeDX,2) + Math.pow(homeDY,2));
      var homeForce=homeDistance*0.01;
      var homeAngle=Math.atan2(homeDY,homeDX);
      
      var cursorForce=0;
      var cursorAngle=0;
      
      if(mx >= 0)
      {
        var cursorDX=this.x-mx;
        var cursorDY=this.y-my;
        var cursorDistanceSquared=Math.pow(cursorDX,2) + Math.pow(cursorDY,2);
        cursorForce=Math.min(10000/cursorDistanceSquared,10000);
        cursorAngle=Math.atan2(cursorDY,cursorDX);
      }
      else
      {
        cursorForce=0;
        cursorAngle=0;
      }
      
      this.xVelocity+=homeForce*Math.cos(homeAngle) + cursorForce*Math.cos(cursorAngle);
      this.yVelocity+=homeForce*Math.sin(homeAngle) + cursorForce*Math.sin(cursorAngle);
      
      this.xVelocity*=0.92;
      this.yVelocity*=0.92;
      
      this.x+=this.xVelocity;
      this.y+=this.yVelocity;
    }
  
    function $(id)
    {
      return document.getElementById(id);
    }
    
    function timer()
    {
      if(!timerRunning)
      {
        timerRunning=true;
        setTimeout(timer,33);
        for(var i=0;i<pixels.length;i++)
        {
          pixels[i].move();
        }
        
        drawPixels();
        wordsTxt.focus();
        
        n++;
        if(n%10==0 && (cw!=document.body.clientWidth || ch!=document.body.clientHeight)) body_resize();
        timerRunning=false;
      }
      else
      {
        setTimeout(timer,10);
      }
    }
    
    function drawPixels()
    {
      var imageData=ctx.createImageData(cw,ch);
      var actualData=imageData.data;
    
      var index;
      var goodX;
      var goodY;
      var realX;
      var realY;
      
      for(var i=0;i<pixels.length;i++)
      {
        goodX=Math.floor(pixels[i].x);
        goodY=Math.floor(pixels[i].y);
        
        for(realX=goodX-resHalfFloor; realX<=goodX+resHalfCeil && realX>=0 && realX<cw;realX++)
        {
          for(realY=goodY-resHalfFloor; realY<=goodY+resHalfCeil && realY>=0 && realY<ch;realY++)
          {
            index=(realY*imageData.width + realX)*4;
            actualData[index+3]=255;
          }
        }
      }
      
      imageData.data=actualData;
      ctx.putImageData(imageData,0,0);
    }
    
    function readWords()
    {
      words=$('wordsTxt').value;
      txt=words.split('\n');
    }
    
    function init()
    {
      readWords();
      
      var fontSize=200;
      var wordWidth=0;
      do
      {
        wordWidth=0;
        fontSize-=5;
        wordCtx.font=fontSize+"px sans-serif";
        for(var i=0;i<txt.length;i++)
        {
          var w=wordCtx.measureText(txt[i]).width;
          if(w>wordWidth) wordWidth=w;
        }
      } while(wordWidth>cw-50 || fontSize*txt.length > ch-50)
      
      wordCtx.clearRect(0,0,cw,ch);
      wordCtx.textAlign="center";
      wordCtx.textBaseline="middle";
      for(var i=0;i<txt.length;i++)
      {
        wordCtx.fillText(txt[i],cw/2,ch/2 - fontSize*(txt.length/2-(i+0.5)));
      }
      
      var index=0;
      
      var imageData=wordCtx.getImageData(0,0,cw,ch);
      for(var x=0;x<imageData.width;x+=resolution) //var i=0;i<imageData.data.length;i+=4)
      {
        for(var y=0;y<imageData.height;y+=resolution)
        {
          i=(y*imageData.width + x)*4;
          
          if(imageData.data[i+3]>128)
          {
            if(index >= pixels.length)
            {
              pixels[index]=new Pixel(x,y);
            }
            else
            {
              pixels[index].homeX=x;
              pixels[index].homeY=y;
            }
            index++;
          }
        }
      }
      
      pixels.splice(index,pixels.length-index);
    }
    
    function body_resize()
    {
      cw=document.body.clientWidth;
      ch=document.body.clientHeight;
      canv.width=cw;
      canv.height=ch;
      wordCanv.width=cw;
      wordCanv.height=ch;
      
      init();
    }
    
    wordsTxt.focus();
    wordsTxt.value=l.substring(index + 3);
    
    resHalfFloor=Math.floor(resolution/2);
    resHalfCeil=Math.ceil(resolution/2);
    
    body_resize();
    timer();
  </script>