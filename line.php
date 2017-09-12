 <?php
  

function send_LINE($msg){
 $access_token = '3NZ4tPcC9W1t6cPI0r3ezvnsoK8KW04hbCSPxKSahSeGbeUU7lC8PQvx02uN5UyL7wOaVJ6EZ9oM5uQjkqLDNZtagQuRcS/NaaGmtopk7pBGOXtNk3lDc4KQIns5tV/jpm8yyr/114JL4uORE5czWwdB04t89/1O/w1cDnyilFU='; 

  $messages = [
        'type' => 'text',
        'text' => $msg
        //'text' => $text
      ];

      // Make a POST Request to Messaging API to reply to sender
      $url = 'https://api.line.me/v2/bot/message/push';
      $data = [

        'to' => 'Ue77a191627f6ac91899e75d92264310c',
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
$msg = "TEST";
send_LINE($msg);
?>
