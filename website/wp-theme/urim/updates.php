<?php
/*
Template Name: Urim updates
*/

  header('Content-Type: application/xml');

  global $wp_query;
  $postid = $wp_query->post->ID;
  $latestVersion = get_post_meta($postid, 'urim-latest-version', true);

  $xml =
'<?xml version="1.0" encoding="utf-8"?>
<app>
    <name>Urim</name>
    <latest-version>'.$latestVersion.'</latest-version>
</app>';
  print($xml);
?>
<?php

?>
