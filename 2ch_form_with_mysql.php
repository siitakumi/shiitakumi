<?php
try{
	//DBへ接続
	$dsn = 'mysql:dbname=co_666_99sv_coco_com;host=localhost';
	$user = 'co-666.99sv-coco';
	$pass = '9BY4wUYS';
	$pdo = new PDO($dsn,$user,$pass,array(PDO::ATTR_EMULATE_PREPARES=>false));

	// SQL作成	
	$sql = 'CREATE TABLE 2ch_tb(num_cun INT AUTO_INCREMENT PRIMARY KEY,name VARCHAR(15),comment TEXT,registry_date DATETIME, password char(16))engine=innodb default charset=utf8';
	//SQL実行
	$stmt = $pdo->query($sql);

}catch(PDOException $e){
	echo "接続失敗しました。<br />";
	echo $e->getMessage();
	die();
}

$edit_mode=0;
?>


<?php
//パスワード、番号が入力されたら編集機能-----------------------------------------------------------------------
//フォームに再表示させる仕様要求を満たすため、フォーム部分プログラムの上の位置にした。
//編集指定フォームで編集対象番号とパスワードが入力された状態で入力ボタンを押した場合
if(isset($_POST['edit_pass']) && !empty($_POST['password']) && !empty($_POST['edit_num'])){
	
	$password = mysql_real_escape_string($_POST['password']);
	$edit_num = mysql_real_escape_string($_POST['edit_num']);
	
	//データベースの中の2ch_tbで投稿番号とパスワードが一致する場所のみ編集する
	//SQL作成用SQL文（データ抽出）
	$sql = "SELECT * FROM 2ch_tb WHERE num_cun='$edit_num' && password='$password';";
	//2次元配列として取得。整数連番をキー、カラム群を値とする配列
	$stmt = $pdo->query($sql);
	
	foreach($stmt as $row){
		//パスワードと投稿番号が共に該当した場合
		if($edit_num == $row['num_cun'] && $password == $row['password']){
			$edit_mode = 1;
			$edit_namae = $row['name'];
			$edit_comment = $row['comment'];
			$edit_pass = $row['password'];
			break;
		}
		else{

echo <<<EOM
			<script type="text/javascript">alert( "対象の投稿が存在しないか、パスワードが違います。" )</script>
EOM;

		}
	}
}
//パスワード、編集対象番号のいずれかもしくは両方が未入力の場合のエラー警告メッセージ
else if(isset($_POST['edit_pass']) && empty($_POST['password']) && !empty($_POST['edit_num'])){
echo <<<EOM
	<script type="text/javascript">alert( "パスワードが入力されていません。" )</script>
EOM;
}
else if(isset($_POST['edit_pass']) && !empty($_POST['password']) && empty($_POST['edit_num'])){
echo <<<EOM
	<script type="text/javascript">alert( "編集対象番号が入力されていません。" )</script>
EOM;
}
else if(isset($_POST['edit_pass']) && empty($_POST['password']) && empty($_POST['edit_num'])){
echo <<<EOM
	<script type="text/javascript">alert( "パスワードと編集対象番号が入力されていません。" )</script>
EOM;
}
?>

<html>
	<head>
		<h1>ハッピー根真面目チームスレwwwwwwww</h1>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
		<title>しいたけのPHP練習用サイト</title>
	</head>
	
	<body>
		<form action = "mission2-15.php" method = "post">
		ニックネーム、パスワード、コメントを入力してください。<br />
		注意：記号「<>」は使用しないでください。
		<font size="4" color = "red">なんかあの…えっと…なんか良くないので。</font><br /><br />
		ニックネーム：<input type = "text" name = "info[namae]" placeholder ="名無しさん" value = "<?= $edit_namae ?>"/><br />
		パスワード　：<input type = "text" name = "info[password]" value = "<?= $edit_pass ?>" /><br />
<textarea name = "info[comment]" rows = "4" cols = "50" placeholder = "ここにコメントを書いてください。"><?= $edit_comment ?></textarea></textarea><br />
		
		<input type = "submit" name = "send_b" value = "送信" />
		<input type = "reset" value = "リセット"><br />
		<input type = "hidden" name = "edit_mode" value = "<?= $edit_mode ?>" />
		<input type = "hidden" name = "edit_num" value = "<?= $edit_num ?>" /><br />
		</form>
		<!-削除用フォーム->
		<form action = "mission2-15.php" method = "post">
		削除したい投稿がある場合は削除ボタンを押してください。
		<input type = "submit" name = "del_b" value = "削除"/>
		</form>
		<!-編集用フォーム作成->
		<form action = "mission2-15.php" method = "post">
		編集したい投稿がある場合は編集ボタンを押してください。
		<input type = "submit" name = "edit_b" value = "編集"/><br /><br />
		</form>
		
	</body>
</html>



<?php
//投稿モード：[送信ボタンが押された、かつ、edit_modeが0かつニックネーム、パスワード、コメントいずれも入力されている]------------------------------------------------
$info = $_POST['info'];//先に入力された名前コメントパスを短い変数名の変数に格納
if(isset($_POST['send_b']) && ($_POST['edit_mode'] == 0) && !empty($info['namae']) && !empty($info['password']) && !empty($info['comment'])){

	$name = $info['namae'];
	$info['comment'] = ereg_replace("\r\n|\n|\r","<br />",$info['comment']);
	$comment = $info['comment'];
	$date = date('Y/m/d H:i:s');
	$password = $info['password'];

	//SQL作成用のSQL文(データベースにフォーム入力されたデータを挿入する)
	//プリペアドステートメントを用意する
	$sql = $pdo->prepare("INSERT INTO 2ch_tb(name,comment,registry_date,password) VALUES(:name,:comment,:registry_date,:password);");
	$sql->bindParam(':name',$name,PDO::PARAM_STR);
	$sql->bindParam(':comment',$comment,PDO::PARAM_STR);
	$sql->bindParam(':registry_date',$date,PDO::PARAM_STR);
	$sql->bindParam(':password',$password,PDO::PARAM_STR);
	$sql->execute();
	
}
//1つ以上未入力があったらエラー警告メッセージ----------------------------------------------------------------------------------------------------------------------
else if(isset($_POST['send_b']) && ($_POST['edit_mode'] == 0) && empty($info['namae']) && !empty($info['password']) && !empty($info['comment'])){
echo <<<EOM
	<script type="text/javascript">alert( "ニックネームが入力されていません。" )</script>
EOM;
}
else if(isset($_POST['send_b']) && ($_POST['edit_mode'] == 0) && !empty($info['namae']) && empty($info['password']) && !empty($info['comment'])){
echo <<<EOM
	<script type="text/javascript">alert( "パスワードが入力されていません。" )</script>
EOM;
}
else if(isset($_POST['send_b']) && ($_POST['edit_mode'] == 0) && !empty($info['namae']) && !empty($info['password']) && empty($info['comment'])){
echo <<<EOM
	<script type="text/javascript">alert( "コメントが入力されていません。" )</script>
EOM;
}
else if(isset($_POST['send_b']) && ($_POST['edit_mode'] == 0) && empty($info['namae']) && empty($info['password']) && !empty($info['comment'])){
echo <<<EOM
	<script type="text/javascript">alert( "ニックネームとパスワードが入力されていません。" )</script>
EOM;
}
else if(isset($_POST['send_b']) && ($_POST['edit_mode'] == 0) && empty($info['namae']) && !empty($info['password']) && empty($info['comment'])){
echo <<<EOM
	<script type="text/javascript">alert( "ニックネームとコメントが入力されていません。" )</script>
EOM;
}
else if(isset($_POST['send_b']) && ($_POST['edit_mode'] == 0) && !empty($info['namae']) && empty($info['password']) && empty($info['comment'])){
echo <<<EOM
	<script type="text/javascript">alert( "パスワードとコメントが入力されていません。" )</script>
EOM;
}
else if(isset($_POST['send_b']) && ($_POST['edit_mode'] == 0) && empty($info['namae']) && empty($info['password']) && empty($info['comment'])){
echo <<<EOM
	<script type="text/javascript">alert( "全て未入力です。" )</script>
EOM;
}
?>



<?php
//編集機能前のパスワード認証----------------------------------------------------------------------------------------
//編集ボタン押されたら、新たにパスワード項目と編集対象番号項目があるフォームを表示
if(isset($_POST['edit_b'])){
?>
	<!-編集指定用フォーム->
	<html>
		<form action ="mission2-15.php" method = "post">
		パスワードと編集したい投稿番号を<font color = "red">半角数字</font>で入力してください。<br />
		対象番号：<input type = "text" name = "edit_num" /><br />
		password：<input type = "text" name = "password" /><br />
		<input type = "submit" name = "edit_pass" value = "入力" /><br /><br />
		</form>
	</html>
<?php
}
//----------------------------------------------------------------------------------------------------------------
?>



<?php
//編集モード（送信ボタンを押されたかつedit_modeが1の場合）------------------------------------------------------------------------------------------
if( isset($_POST['send_b']) && ($_POST['edit_mode'] == 1) ){

	$edit_mode = 0;
	$edit_num = $_POST['edit_num'];
	$name = $info['namae'];
	$info['comment'] = ereg_replace("\r\n|\n|\r","<br />",$info['comment']);
	$comment = $info['comment'];
	$password = $info['password'];
	$date = date('Y/m/d H:i:s');	
	echo "入力内 ".$edit_num." ".$name." ".$comment." ".$password."<br />";

	$sql = "update 2ch_tb set name = '$name' ,comment = '$comment',password = '$password' where num_cun = '$edit_num';"; 
	$stmt = $pdo->query($sql);

echo <<<EOM
<script type="text/javascript">alert( "編集が完了しました。" )</script>
EOM;
}

//1つ以上未入力があったらエラー警告メッセージ---------------------------------------------------------------------------------------------------------
else if(isset($_POST['send_b']) && ($_POST['edit_mode'] == 1) && empty($info['namae']) && !empty($info['password']) && !empty($info['comment'])){
echo <<<EOM
	<script type="text/javascript">alert( "ニックネームが入力されていません。" )</script>
EOM;
}
else if(isset($_POST['send_b']) && ($_POST['edit_mode'] == 1) && !empty($info['namae']) && empty($info['password']) && !empty($info['comment'])){
echo <<<EOM
	<script type="text/javascript">alert( "パスワードが入力されていません。" )</script>
EOM;
}
else if(isset($_POST['send_b']) && ($_POST['edit_mode'] == 1) && !empty($info['namae']) && !empty($info['password']) && empty($info['comment'])){
echo <<<EOM
	<script type="text/javascript">alert( "コメントが入力されていません。" )</script>
EOM;
}
else if(isset($_POST['send_b']) && ($_POST['edit_mode'] == 1) && empty($info['namae']) && empty($info['password']) && !empty($info['comment'])){
echo <<<EOM
	<script type="text/javascript">alert( "ニックネームとパスワードが入力されていません。" )</script>
EOM;
}
else if(isset($_POST['send_b']) && ($_POST['edit_mode'] == 1) && empty($info['namae']) && !empty($info['password']) && empty($info['comment'])){
echo <<<EOM
	<script type="text/javascript">alert( "ニックネームとコメントが入力されていません。" )</script>
EOM;
}
else if(isset($_POST['send_b']) && ($_POST['edit_mode'] == 1) && !empty($info['namae']) && empty($info['password']) && empty($info['comment'])){
echo <<<EOM
	<script type="text/javascript">alert( "パスワードとコメントが入力されていません。" )</script>
EOM;
}
else if(isset($_POST['send_b']) && ($_POST['edit_mode'] == 1) && empty($info['namae']) && empty($info['password']) && empty($info['comment'])){
echo <<<EOM
	<script type="text/javascript">alert( "全て未入力です。" )</script>
EOM;
}
//ここまで編集モードエラーメッセージ---------------------------------------------------------------------------------------------------------------
?>



<?php
//削除機能前のパスワード認証-------------------------------------------------------------------------------------------
//削除ボタン押されたら新たにパスワード項目と削除対象番号項目があるフォームを表示
if(isset($_POST['del_b'])){
?>
<html>
<head>

	<script type = "text/javascript">
	function del_sure(){
		return confirm("あなたの心に問いかけてください。本当に削除しますか？");
	}
	</script>

<head>
	<form action ="mission2-15.php" onSubmit = "return del_sure();" method = "post">
	パスワードと削除したい投稿番号を<font color = "red">半角数字</font>で入力してください。<br />
	対象番号：<input type = "text" name = "del_num" /><br />
	password：<input type = "text" name = "password" /><br />
	<input type = "submit" name = "del_pass" value = "入力" /><br /><br />
	</form>
</html>
<?php
}
//パスワード、番号が入力されてる状態で入力ボタン押したら削除機能へ-------------------------------------------------------
if(isset($_POST['del_pass']) && !empty($_POST['password']) && !empty($_POST['del_num'])){

	$del_num = $_POST['del_num'];
	$password = $_POST['password'];	
	
	$sql = "SELECT * FROM 2ch_tb WHERE num_cun = :del_num && password = :password";
	$stmt = $pdo->prepare($sql);
	$stmt -> bindParam(":del_num",$del_num,PDO::PARAM_STR);
	$stmt -> bindParam(":password",$password,PDO::PARAM_STR);	
	$stmt -> execute();

	foreach($stmt as $row){
		$tar_num = $row['num_cun'];
		$tar_pass = $row['password'];
	}

	//パスワードと投稿番号が共に該当した場合削除
	if($tar_num == $del_num && $tar_pass == $password){

		$sql = "update 2ch_tb set name = '' ,comment = 'この投稿は削除されました。',password = '1' where num_cun = '$del_num';"; 
		//基本的にパスワードは1としている。
		//$sql = "delete from 2ch_tb where num_cun = '$del_num';"; 
		//$sql = ALTER TABLE table_name AUTO_INCREMENT = 1
		$stmt = $pdo -> query($sql);

		echo <<< EOM
		<script type = "text/javascript">alert("対象の投稿は削除されました。")</script>
EOM;
	}
	else{

echo <<<EOM
		<script type="text/javascript">alert( "対象の投稿が存在しないか、パスワードが違います。" )</script>
EOM;
	}
}
////1つ以上未入力があったらエラー警告メッセージ-----------------------------------------------------------------------------------------------------
else if(isset($_POST['del_pass']) && empty($_POST['password']) && !empty($_POST['del_num'])){
echo <<<EOM
	<script type="text/javascript">alert( "パスワードが入力されていません。" )</script>
EOM;
}
else if(isset($_POST['del_pass']) && !empty($_POST['password']) && empty($_POST['del_num'])){
echo <<<EOM
	<script type="text/javascript">alert( "削除対象番号が入力されていません。" )</script>
EOM;
}
else if(isset($_POST['del_pass']) && empty($_POST['password']) && empty($_POST['del_num'])){
echo <<<EOM
<script type="text/javascript">alert( "パスワードと削除対象番号が入力されていません。" )</script>
EOM;
}
//ここまで削除モードエラーメッセージ------------------------------------------------------------------------------------------------------------------
?>

<?php
//投稿された内容は常に全表示（位置は全フォームの下）---------------------------------------------------------------------------------------------------
//表示(投稿番号：ニックネーム：時間：改行：コメント:改行改行)
$sql = 'SELECT * FROM 2ch_tb ORDER BY num_cun DESC;';
$stmt = $pdo->query($sql);

//データがある場合表示する
if($stmt != false){
	foreach($stmt as $row){
		echo "<hr>";
		echo $row['num_cun']." ".$row['name']." ".$row['registry_date']."<br />".$row['comment']."<br />" /*.$row['password']*/ ."<br /><br />";
	}
}else{
	echo "まだ誰も投稿していません。<br />";
}
//接続を閉じる
$pdo = null;
?>