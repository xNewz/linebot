 <?php
  

function send_LINE($msg){
 $access_token = 'vyI+PkQx+j0n0Pa/GizyotGcn/uz6l86WYbWljuhi9GKi/P4NyInP8Nh3cJi+pJhVKPDVigwlDBJCjI+2pMnY1Bv1xADgvLjDabFFGG7ugmtSILP6eNwD9m6avUzci8uLo2faRUDQe9+rVAxG779lwdB04t89/1O/w1cDnyilFU='; 

  $messages = [
        'type' => 'text',
        'text' => $msg
        //'text' => $text
      ];

      // Make a POST Request to Messaging API to reply to sender
      $url = 'https://api.line.me/v2/bot/message/push';
      $data = [

        'to' => 'U81a5007f0ac3c2b742a2837836fe59f6',
        'messages' => [$messages],
      ];
      $post = json_encode($data);
      $headers = array('Content-Type: application/json', 'Authorization: Bearer ' . $access_token);

      $ch = curl_init($url);
      curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "POST");
      curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
      curl_setopt($ch, CURLOPT_POSTFIELDS, $post);
      curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
      curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 1);
      $result = curl_exec($ch);
      curl_close($ch);

      echo $result . "\r\n"; 
}

?>
