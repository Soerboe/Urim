<?php
/*
Template Name: Urim updates
*/

  header('Content-Type: application/xml');

  global $wp_query;
  $postid = $wp_query->post->ID;
  $latestVersion = get_post_meta($postid, 'urim-latest-version', true);

  $downloadPage = get_page_by_title('Downloads');
  $downloadPageUrl = get_page_link($downloadPage->ID);

  $xml =
'<?xml version="1.0" encoding="utf-8"?>
<app>
    <name>Urim</name>
    <latest-version>' . $latestVersion . '</latest-version>
    <download-page-url>' . $downloadPageUrl . '</download-page-url>
</app>';
  print($xml);
?>
<?php

?>
