#php&mysql
##目标
实现php与mysql链接，通过php获取后端数据。
##功能设计
>####1.连接数据库
>通过在程序中执行php脚本，能够使用指定的用户名登录数据库。在数据库的操作层面，通过登陆的用户名的不同角色给予不同的权限，实现对数据库安全的保护。
>####2.读取数据库信息
>在登录的情况下，根据php传入的读取数据库的表、列等数据的读取请求信息，首先检查用户权限，若有对该数据的读权限，则执行sql语句，将指定的数据返回。
>####3.向数据库中写入
>在登录的情况下，根据php传入的写入数据库的表、列等数据的覆写请求信息，检查用户权限，若权限正确，则执行sql语句，将传入的数据写入sql数据库中并保存。
>####4.对数据进行逻辑操作
>得到读取的信息之后，将所读到的信息进行展示或与操作值进行比较，后者通常返回bool值，表示操作的成功与否。
##链接
>MySQL 可应用于多种语言，包括 PERL, C, C++, JAVA 和 PHP。 在这些语言中，Mysql在PHP的web开发中是应用最广泛。  
>本地服务器的选择上，我们选择了同时童工mysql和php功能的wampserver，
>修改默认根目录为安装目录下www文件夹内新建文件夹testmyphp文件夹，并将所有php文件放在此文件家长方便使用。
>使用mysqli扩展
>
    <?php
    $servername = "localhost";
    $username = "username";
    $password = "password";
    // 创建连接
    $conn = new mysqli($servername, $username, $password);
    // 检测连接
    if ($conn->connect_error) {
        die("连接失败: " . $conn->connect_error);
    } 
    echo "连接成功";
    ?>
    
##数据操作
>reference:  
>[PHP+MySql实现后台数据的读取](https://www.cnblogs.com/cherishli/p/7077787.html)  
>[C#通过php像mysql中插入数据的的编码问题](https://blog.csdn.net/mushiqingchang/article/details/47322335)
>###1.读取数据
>是用户登录、课程&成绩查询的必备操作  
>以登录为例，得到输入的用户名密码之后，php脚本通过sql语句访问以列名确定的列，经过判断匹配后将结果输出
>
    <?php
        header("Content-Type:text/html;charset=utf-8");include_once("../mysql/mysql.php");
        $userName = $_POST["userName"];
        $pwd = $_POST["pwd"];
        $loginSql = <<<login
        select * from submit where username="{$userName}" and pwd = "{$pwd}";
    login;
        $res = mysqli_query($con, $loginSql);  
        if($row = mysqli_fetch_row($res)){
            $_SESSION["user"] = $row;
            echo "登录成功";
        }else{
            echo "登录失败";
        }  
        mysqli_free_result($res);
        mysqli_close($con);
    ?>
>###2.写入数据
>主要是在注册、教师对课程管理、录入成绩的用途。  
>以注册为例进行分析实现。接收到客户端输入的用户名和密码之后，根据指定的列名，对库中的数据进行检索，如果有重复数据则注册失败，反之在数据库中进行添加<code>INSERT</code>操作，理论上禁止明文存储密码信息，应该将密码转化为md5值或其他不可逆信息进行存储，保障用户数据安全。
>
    <?php
        header("Content-Type:text/html;charset=utf-8");
        $str=$_POST["formData"];
        list($username)=explode("&", $str);
        list(,$pwd)=explode("&", $str);
        list(,,,$realname)=explode("&", $str);
        list(,$username)=explode("=", $username);
        list(,$pwd)=explode("=", $pwd);
        list(,$realname)=explode("=", $realname);
        include_once("mysql.php");
        $sql=<<<sql
        insert into submit (username,pwd,realname) values ("$username","$pwd","$realname");
    sql;
        $sql2=<<<sql2
        SELECT username FROM submit WHERE username="$username";
    sql2;
        $res2=mysqli_query($con, $sql2);
        $res=mysqli_query($con, $sql);
        if(mysqli_num_rows($res2)>0){
            die("用户名已经存在！");  
        }
        elseif($res){
            echo 'true';
        }else{
            die();
        }
    ?>
>###3.对变单数句和数据库数据进行比较
>在以上登录的操作中，取出数据库中的内容之后进行的比较部分即为对数据进行比较操作  
>在注册过程中，客户端读取用户名和设置的密码后经过检验符合标准，应该将密码的md5值存入数据库中，这是对数据的处理变换。(为了防止数据库信息泄露，应禁止明文存储用户密码信息。)