<?php
$access_token = 'vyI+PkQx+j0n0Pa/GizyotGcn/uz6l86WYbWljuhi9GKi/P4NyInP8Nh3cJi+pJhVKPDVigwlDBJCjI+2pMnY1Bv1xADgvLjDabFFGG7ugmtSILP6eNwD9m6avUzci8uLo2faRUDQe9+rVAxG779lwdB04t89/1O/w1cDnyilFU=';    //PUT LINE token ID at "Channel access token (long-lived)"
$url = 'https://api.line.me/v1/oauth/verify';
$headers = array('Authorization: Bearer ' . $access_token);

$ch = curl_init($url);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 1);

$result = curl_exec($ch);
curl_close($ch);

echo $result;
?>
