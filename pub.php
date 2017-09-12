 <?php
  
   function pubMqtt($topic,$msg){
       
      put("https://api.netpie.io/topic/numpapicklinebot/$topic?retain",$msg);
 
  }
  function getMqttfromlineMsg($lineMsg,$replytoken){
 
    $pos = strpos($lineMsg, ":");
    if($pos){
      $splitMsg = explode(":", $lineMsg);
      $topic = $splitMsg[0];
      $msg = $splitMsg[1];
      pubMqtt($topic,$msg);
    }else{
      $topic = $replytoken;
      $msg = $lineMsg;
      pubMqtt($topic,$msg);
    }
  }
 
  function put($url,$tmsg)
{
      
    $ch = curl_init($url);
 
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);    
     
    curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 10);
     
    curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
     
    curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "PUT");
     
    curl_setopt($ch, CURLOPT_POSTFIELDS, $tmsg);
 
    curl_setopt($ch, CURLOPT_USERPWD, "{mJ7K4MfteC7p0dW}:{pp4gzMhCvJIqlxc66hKEvk46m}");
     
    $response = curl_exec($ch);
     
    curl_close ($ch);
     
    return $response;
}
  $masss = "1";
 getMqttfromlineMsg($masss);
?>
