<?php
/*
Template Name: Urim updates
*/


  $lang = $_GET['lang'];
  if (empty($lang)) {
    $lang = 'en'; // english default language
  }

  global $wp_query;
  $postid = $wp_query->post->ID;
  $latestVersion = get_post_meta($postid, 'urim-latest-version', true);
  $downloadPageTitle = get_post_meta($postid, 'download-page-' . $lang, true);

  if (!$latestVersion || !$downloadPageTitle) {
    http_response_code(500);
    exit(-1);
  }

  $downloadPage = get_page_by_title($downloadPageTitle);
  $downloadPageUrl = get_page_link($downloadPage->ID);

  $xml =
'<?xml version="1.0" encoding="utf-8"?>
<app>
    <name>Urim</name>
    <latest-version>' . $latestVersion . '</latest-version>
    <download-page-url>' . $downloadPageUrl . '</download-page-url>
</app>';

  header('Content-Type: application/xml');
  print($xml);
?>
