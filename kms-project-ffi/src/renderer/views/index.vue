<template>
  <div>
    <el-form>
      <el-input v-bind="symmKey" :value="symmKey">
        
      </el-input>
    </el-form>
    <el-button @click="submit" type="danger">生成对称密钥</el-button>
    <!-- <img src="@/assets/logo.png"/> -->
    <el-button @click="test" type="danger">test</el-button>
    <el-button @click="sm2test" type="danger">sm2 test</el-button>
  </div>
  
  
</template>

<script>


/***********************nodejs调dll*********************************** */
const iconv  = require('iconv-lite')
const ref = require('ref')
const refArray = require('ref-array')
const remote = require("electron").remote;
const ffi = remote.require("ffi");
const fastJson = require('fast-json-stringify');

const sk = refArray(ref.types.uchar,20);
const pk = refArray(ref.types.uchar,2065);
var ucharPtr = ref.refType('uchar');
const sm2 = require('sm-crypto').sm2
const sm3 = require('sm-crypto').sm3
const sm4 = require('sm-crypto').sm4

var DLL2 = ffi.Library('dll/Dll2.dll',{
    "foo": [ "int", ["int"] ],
  "bar": [ "int", [] ],
  "testKey":["int",["string","int"]],
  "testKey1":["int",["string","int"]]
});
var DLL = ffi.Library('dll/Dll1.dll', {
        'foo': [
            'int', ['int'],
        ],
    'Add': ['double', ['double', 'double'], ],
    'AddStr': ['int', ['string', 'string'], ],
    'ResultStr': ['string', ['string', 'string'], ],
    'test': [ref.refType(sk), ['uchar*', 'int','string', 'int'], ],
    'resolveBufer': ['void', ['string', 'int'], ],
    'resolveUBufer': ['void', ['uchar*', 'int'], ],
    'get_md5_string': ['void', ['char*'], ],
    'testInt': ['int', ['int**', 'int'], ],
    'testStr': ['int', ['string','int' ,'string','int'], ],
    }); 
var csf_DLL = ffi.Library('dll/csf_vs_dll.dll', {
        'cs_rand_bytes_generate': [
            'int', ['string','int']]
    });
/***********************nodejs调java*********************************** */
  export default {
    name: 'intercom',
    data(){
      return{
          sysSigPubStr: new Buffer("BY9y0RDaQpxQz2+Rp1Nto5nRn8hYZS5OQvpjQUXWNonPnZS2qAfZTkp0DscljkX54SXmKYixt4yzY/L9TRdLwA==",'base64'),
          sysCipPubStr: new Buffer( "tByVc29AvdwbGo59q2mzxsyINqDlO8IzpQ1MY0xQPWOl018ErAXXqlksttQdqAad8ROkE+3rPc1ScvFyBRkh0A==",'base64'),
          sigPubStr : new Buffer( "ZRzQTldVMvkfH3mQJOMYnRWPZzBGllUg1wHT8EeTSXdjTCuFifKxM/I2N+7WgDGMkL/X/4eu4u68fqUBTPd/LQ==",'base64'),
          sigPriStr : new Buffer( "nNc9oSNDO1rCjyA7jMAfCLgqQ2SEYVtR7dcBgyyJsVA=",'base64'),
          cipPubStr : new Buffer( "CZ3kpxB98u7sh/OOcogFtBfvtQwqc70YDbXkW+K9KDXVdCF4adYlQiIsVM6SK9W160rauxnOR1bwRDEly4jfEA==",'base64'),
          cipPriStr : new Buffer( "9DxcXO+Wei+bOU93BDZp/tJ6fhJBE88ZKgSLRdkhDqA=",'base64'),


        symmKey:"",
        symmKeyPointer:"",
        bbuf:""
      }
    },
    created(){

      // this.symmKey=
      // console.log(DLL.Add("1.0", "2.0")) 
    },
    methods:{
      test(){
        // var inputInt = ref.alloc("int*");
        // DLL.testInt(inputInt,inputInt.length)
        // console.log(inputInt.deref())
        // let Count = ref.deref(inputInt);
        // console.log(Count)
        // var str1 = new Buffer(20)
        // var str2 = new Buffer(20)
        // let result = DLL.testStr(str1,str1.length,str2,str2.length)
        // console.log("1")
        // console.log(result)
        // console.log("2")
        // console.log(ref.readCString(str1, 0))
        // console.log("1")
        // console.log(ref.readCString(str2, 0))
        // console.log(ref.readCString(result, 0))
        // var key = ref.alloc("char*");
        
        var keyBuffer = new Buffer(32);
        // let key = "123";
        // keyBuffer.refType("string")
        
        let result =100;
        result =csf_DLL.cs_rand_bytes_generate(keyBuffer,32);
    
        var key = ref.readCString(keyBuffer, 0);
        
        console.log("生成随机数返回值：")
        console.log(result)
        console.log("生成随机数："+key)
        console.log()
        var md5Buffer = new Buffer(32);
        DLL.get_md5_string(md5Buffer);
        var actualString = ref.readCString(md5Buffer, 0);
        console.log("生成MD5："+actualString)
        var addres = DLL.Add(0.2,0.3)
        console.log("add："+addres)
        var dll2add=DLL2.foo(2);
        console.log("dll2 add："+dll2add)
        var keyBuffer2 = new Buffer("aajs:testKey");
        // keyBuffer2="aajs:testKey";
        DLL2.testKey(keyBuffer2,12)
        var keyBuffer2String = ref.readCString(keyBuffer2, 0);
        console.log("dll2 testKey:"+keyBuffer2String)

        var keyBuffer21 = new Buffer("ajs:testKey1");
        keyBuffer21.type=ref.refType('string')
        // keyBuffer21="ajs:testKey1";
        DLL2.testKey1(keyBuffer21,12)
        var keyBuffer2String1 = ref.readCString(keyBuffer21, 0);
        
        console.log("dll2 testKey1:"+keyBuffer2String1)
        

      },
      submit(){
        var inputUnchar = new Buffer(10)
        var inputstr = new Buffer(20)
        var returnstr = new Buffer(20)
        // inputbf[0]=127
        // inputbf[1]=129
        
        returnstr=DLL.test(inputUnchar,inputUnchar.length,inputstr,inputstr.length)
        console.log(returnstr)
        // returnstr.type=ref.refType('uchar')
        // console.log(returnstr.deref())
        // console.log("1")
        // console.log(ref.readCString(returnstr, 0))
        // console.log("2")
        // console.log(ref.readCString(inputUnchar, 0))
        // console.log(returnstr)
        // var as_data  =  iconv.encode(returnstr,'utf8')
        // console.log("c test return:")
        // console.log(ucharPtr.deref())

        // console.log(as_data)
        // console.log(returnsk)
        // var as_data  =  iconv.encode(resultbf,'utf8')
        // console.log("转换为utf16")
        // console.log(as_data)
        // DLL.resolveBufer(resultbf,resultbf.length)
        // let stringData = ref.alloc('string')
        // var buf = new Buffer(64);
        // 
        // var buf = "";
        // this.bbuf ="";
        // this.bbuf.type="string"
        
        // var result = DLL.AddStr(buf,this.bbuf)

        // var resultStr = DLL.ResultStr(buf,this.bbuf)
        // console.log("resultStr"+resultStr)
        // console.log(buf)
        // console.log("result:"+result)
        // console.log(buf.hexAddress())
        // console.log(buf.deref())
        // console.log(ref.readCString(buf))
        // console.log(buf)
        // console.log("bbuf")
        // console.log(this.bbuf) 
        // console.log(resultStr) 
        // console.log(ref.readCString(this.bbuf))
        // console.log(this.bbuf.deref()) 
        
        // var result = csf_DLL.cs_rand_bytes_generate(buf,64)
        // console.log("result:"+result)
        // var as_data  =  iconv.encode(buf,'gbk')
        // console.log("buf:"+buf.toString("ascii"))
        // console.log(ref.readCString(buf))
        // console.log("111111111:"+buf.toString("ascii"))
        // console.log("111111111:"+buf)
        // console.log("symmKeyPointer:"+this.symmKeyPointer)
        // console.log("symmKeyPointer:"+buf.deref())
        // this.symmKey = this.symmKeyPointer.deref()
        // console.log("symmKey:"+this.symmKey)

      },
      sm2test(){
        let strSigPubStr=this.sigPubStr.toString("hex")

        let strSigPriStr=this.sigPriStr.toString("hex")

        let hashData = sm3('XDYG')
        console.log("sm3")
        console.log(hashData)


        let keypair = sm2.generateKeyPairHex()
        var publicKey = keypair.publicKey // 公钥
        var privateKey = keypair.privateKey // 私钥

        console.log(publicKey)
        console.log(privateKey)
        console.log(strSigPubStr)

        
      }
    }
  }
</script>

<style>
  /* CSS */
</style>
