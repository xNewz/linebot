 <?php
  

function send_LINE($msg){
 $access_token = 'Lp06UelnIizZGfybMu2KFy+frr83Ux2wPMFRIKATaTonTHBxFabr8ykcP6pUnttHVKPDVigwlDBJCjI+2pMnY1Bv1xADgvLjDabFFGG7ugnoe4bJoBqk6PbkPIQVxSiv19TWYrwUyWpOjGS83V3CegdB04t89/1O/w1cDnyilFU='; 

  $messages = [
        'type' => 'text',
        'text' => $msg
        //'text' => $text
      ];

      // Make a POST Request to Messaging API to reply to sender
      $url = 'https://api.line.me/v2/bot/message/push';
      $data = [

        'to' => 'a44e281119ae79dac3b1cc0a3f4b4841',
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
