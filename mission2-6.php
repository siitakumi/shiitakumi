<?php
	//共通事項の処理は常にしておく。（配列格納、ファイルチェックなどの前処理）---------------------------------------
	$info = $_POST['info'];
	//テキストエリアに書き込まれた内容で改行があったら、ブラウザ上での改行文字（<br />）に置き換える。
	//第1引数：（置き換えられる対象）改行文字全て　第2引数：（置き換える対象）ブラウザでの改行　第3引数：対象の文字列
	$info['comment'] = ereg_replace("\r\n|\n|\r","<br />",$info['comment']);
	$timestamp = date('Y/m/d H:i:s');
	$file = dirname(__FILE__) . '/kadai2-2.txt';
	
	if(is_file($file)){
		$array = @file($file, FILE_IGNORE_NEW_LINES);
		$num_cun = count( file( $file ) );
		$num_cun++;
		
		foreach($array as $value){
			
			$div_ary = explode("<>",$value);
		}
	}
	//ファイルが無かったら新規作成、変数$arrayに格納
	else{
		$file = 'kadai2-2.txt';
		$array = @file($file, FILE_IGNORE_NEW_LINES);
		$num_cun = 1;
	}
?>



<?php
//パスワード、番号が入力されたら編集機能--------------------------------------------------------
//フォームに再表示させる仕様を満たすため、あえて2-1で作成したフォームプログラムの上の位置にした。
//条件文…編集指定フォームで編集対象番号とパスワードが入力された状態で入力ボタンを押した場合
if(isset($_POST['edit_pass']) && !empty($_POST['password']) && !empty($_POST['edit_num'])){
	
	$is_pass = 0; //password一致判定（最初は0、いわゆる不一致）
	$password = $_POST['password'];
	$edit_num = $_POST['edit_num'];
	
	//ファイルの中身を一行ずつループ
	//<>を区切りに変数$div_aryに格納
	foreach($array as $value){
		$div_ary = explode("<>",$value);
		
		//文字列を比較する場合は===にする必要があるらしい
		//trim()で空白文字、スペースを削除（パスワード入力で空白があるとエラーになったりするから）
		//含まれるパスワードと入力されたパスワードで一致したものがあったらis_passを1（一致）にする
		if(trim($password) === trim($div_ary[3])){
			$is_pass = 1;
		}
	
	}
	
	//パスワードが一致している場合の処理
	if($is_pass == 1){
		
		//ファイルの先頭からループ処理
	    foreach($array as $value){
			$div_ary = explode("<>",$value);
			
			//パスワード一致の状態で対象の番号と編集対象番号が一致してたら
			//入力フォームでvalueにした変数に名前、コメント、パスワードそれぞれ格納すうｒ
			if($div_ary[0] == $edit_num){
				
				$edit_namae = $div_ary[1];
				$edit_comment = $div_ary[2];
				$edit_pass = $div_ary[3];
				$edit_mode = 1;
				
			}
		}
	}
	//パスワードが一致してなかったらjavascriptによるエラー警告メッセージ
	else if($is_pass == 0){	

//IDタグは先頭に記述するようにしないとエラーが起こる
//タグの前後には空白、文字列禁止。終了タグは改行必要
//開始ID、終端IDはEOM（End of Message）にした。
echo <<<EOM
		<script type="text/javascript">alert( "パスワードが違います。" )</script>
EOM;
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



<!DOCTYPE html>
<html>
	<head>
		<h1>ハッピー根真面目チームスレwwwwwwww</h1>
		<!-文字コードはUTF-8に指定>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
		<title>しいたけのPHP練習用サイト</title>
	</head>
	
	<!-本体部->
	<body>
		
		<form action = "mission2-6.php" method = "post">
		ニックネーム、パスワード、コメントを入力してください。<br />
		注意：記号「<>」は使用しないでください。
		<font size="4" color = "red">なんかあの…えっと…なんか良くないので。</font><br /><br />
		ニックネーム：<input type = "text" name = "info[namae]" value = "<?= $edit_namae ?>"/><br />
		パスワード　：<input type = "text" name = "info[password]" value = "<?= $edit_pass ?>" /><br />
		<!-row属性で入力エリアの行数をcol属性で列数を文字数単位で指定している。->
		<!-空白になるのであえて先頭に詰める->
<textarea name = "info[comment]" rows = "4" cols = "50" placeholder = "ここにコメントを書いてください。"><?= $edit_comment ?></textarea></textarea><br />
		
		<input type = "submit" name = "send_b" value = "送信" />
		<input type = "reset" value = "リセット"><br />
		<input type = "hidden" name = "edit_mode" value = "<?= $edit_mode ?>" />
		<input type = "hidden" name = "edit_num" value = "<?= $edit_num ?>" /><br />
		</form>
		<!-削除用フォーム->
		<form action = "mission2-6.php" method = "post">
		削除したい投稿がある場合は削除ボタンを押してください。
		<input type = "submit" name = "del_b" value = "削除"/>
		</form>
		<!-編集用フォーム作成->
		<form action = "mission2-6.php" method = "post">
		編集したい投稿がある場合は編集ボタンを押してください。
		<input type = "submit" name = "edit_b" value = "編集"/><br /><br />
		</form>
		
	</body>
</html>



<?php
//投稿モード：[送信ボタンが押された、かつ、edit_modeが0かつ名前、パスワード、コメントいずれも入力されている]-----------------------------------------------------------
if( isset($_POST['send_b']) && ($_POST['edit_mode'] == 0) && !empty($info['namae']) && !empty($info['password']) && !empty($info['comment'])){
	
	//ファイルを追記モードで開く
	$fp = fopen($file,'a');
	
	//ファイルに新たに書き込む
	fwrite($fp, $num_cun."<>".$info['namae']."<>".$info['comment']."<>".$info['password']."<>".$timestamp ."\n");

	fclose($fp);
}
//1つ以上未入力があったらエラー警告メッセージ----------------------------------------------------------------------------------------------------------------------
else if(isset($_POST['send_b']) && ($_POST['edit_mode'] == 0) && empty($info['namae']) && !empty($info['password']) && !empty($info['comment'])){
echo <<<EOM
	<script type="text/javascript">alert( "名前が入力されていません。" )</script>
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
	<script type="text/javascript">alert( "名前とパスワードが入力されていません。" )</script>
EOM;
}
else if(isset($_POST['send_b']) && ($_POST['edit_mode'] == 0) && empty($info['namae']) && !empty($info['password']) && empty($info['comment'])){
echo <<<EOM
	<script type="text/javascript">alert( "名前とコメントが入力されていません。" )</script>
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
//編集機能前のパスワード認証--------------------------------------------------------------------------------------
//編集ボタン押されたら、新たにパスワード項目と編集対象番号項目があるフォームを表示
if(isset($_POST['edit_b'])){
?>
	<!-編集指定用フォーム->
	<html>
		<form action ="mission2-6.php" method = "post">
		パスワードと編集したい投稿番号を<font color = "red">半角数字</font>で入力してください。<br />
		対象番号：<input type = "text" name = "edit_num" /><br />
		password：<input type = "text" name = "password" /><br />
		<input type = "submit" name = "edit_pass" value = "入力" /><br /><br />
		</form>
	</html>
<?php
}
//編集モード（送信ボタンを押されたかつedit_modeが1の場合）-------------------------------------------------------------------------------------
if( isset($_POST['send_b']) && ($_POST['edit_mode'] == 1) ){
	
	//次は通常モードにするため
	$edi_mode = 0;
	$edit_num = $_POST['edit_num'];	//フォームから送信された編集対象番号
	$fp = fopen($file,'w');
	
	foreach($array as $value){
		$div_ary = explode("<>",$value);
		
		//編集対象番号と一致したらその行のみ修正
		if($div_ary[0] == $edit_num){
			
			$namae = $info['namae'];
			$comment = $info['comment'];
			$password = $info['password'];
			
			fwrite($fp, $edit_num."<>".$namae."<>".$comment."<>".$password."<>".$timestamp."\n");
		}
		else {
			//それ以外はそのまま上書き
			fwrite($fp, $div_ary[0]."<>".$div_ary[1]."<>".$div_ary[2]."<>".$div_ary[3]."<>".$timestamp."\n");
		}
	}
    
	fclose($fp);
}
//1つ以上未入力があったらエラー警告メッセージ-----------------------------------------------------------------------------------------------------
else if(isset($_POST['send_b']) && ($_POST['edit_mode'] == 1) && empty($info['namae']) && !empty($info['password']) && !empty($info['comment'])){
echo <<<EOM
	<script type="text/javascript">alert( "名前が入力されていません。" )</script>
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
	<script type="text/javascript">alert( "名前とパスワードが入力されていません。" )</script>
EOM;
}
else if(isset($_POST['send_b']) && ($_POST['edit_mode'] == 1) && empty($info['namae']) && !empty($info['password']) && empty($info['comment'])){
echo <<<EOM
	<script type="text/javascript">alert( "名前とコメントが入力されていません。" )</script>
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
	//onSubmit()…起動するスクリプトは属性値に"return 関数名()"と書かなければならないイベントハンドラ
	//submitが押された時に起動するスクリプトでtrueを返されるとフォームのアクションを実行。
	//falseが返されると実行を中止する
	<form action ="mission2-6.php" onSubmit = "return del_sure();" method = "post">
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
	$is_pass = 0;
	$del_num = $_POST['del_num'];
	$pass = $_POST['password'];	
	
	foreach($array as $value){
		$div_ary = explode("<>",$value);
		
		//投稿番号とパスワードが共に一致したものがあったらis_passを1にする
		if(trim($pass) === trim($div_ary[3]) && trim($del_num) == trim($div_ary[0])){
			$is_pass = 1;
		}
	}
	
	//パスワードが一致している場合の処理
	if($is_pass == 1){
		$del_num = $_POST['del_num']; //削除対象番号
		$fp = fopen($file,'w');
		$num_cun=1;
	    
		foreach($array as $value){
			$div_ary = explode("<>",$value);
			
			//削除対象番号に一致しない行だけファイルに上書きする
			if($div_ary[0] != $del_num){
				fwrite($fp, $num_cun."<>".$div_ary[1]."<>".$div_ary[2]."<>".$div_ary[3]."<>".$timestamp ."\n");
				$num_cun++;
			}
		
		}

echo <<< EOM
		<script type = "text/javascript">alert("対象の投稿は削除されました。")</script>
EOM;

	}
	//パスワードが一致してない
	else if($is_pass == 0){
echo <<<EOM
	<script type = "text/javascript">alert("パスワードが違います。")</script>
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
$file = dirname(__FILE__) . '/kadai2-2.txt';
$array = @file($file, FILE_IGNORE_NEW_LINES);

if(is_file($file)){
	
	foreach($array as $value){
	
		$div_ary = explode("<>",$value);
		
		//表示(投稿番号：名前：時間：改行：コメント:改行改行)
		echo $div_ary[0]." ".$div_ary[1]." ".$div_ary[4]."<br />".$div_ary[2]."<br /><br />";

	}
}else{
	echo "まだ誰も投稿していません。<br />";
}
?>
