<?php
/*
Template Name: Urim updates
*/


  $lang = $_GET['lang'];
  if (empty($lang)) {
    $lang = 'en'; // english default language
  }

  $currentVersion = $_GET['v'];

  global $wp_query;
  $postid = $wp_query->post->ID;
  $latestVersion = get_post_meta($postid, 'urim-latest-version', true);
  $downloadPageTitle = get_post_meta($postid, 'download-page-' . $lang, true);

  if (!$latestVersion || !$downloadPageTitle || empty($currentVersion)) {
    // http_response_code available in PHP >= 5.4
    //http_response_code(500);
    $error_code = empty($currentVersion) ? 400 : 500;
    header('X-PHP-Response-Code: ' . $error_code, true, $error_code);
    exit(-1);
  }

  header('Content-Type: application/xml');
  $xml =
  '<?xml version="1.0" encoding="utf-8"?>
    <application-info version="1.0">
      <name>Urim</name>';

  $xml .= '<has-update>';
  $xml .= (version_compare($currentVersion, $latestVersion) >= 0) ? 'false' : 'true';
  $xml .= '</has-update>';

  $downloadPage = get_page_by_title($downloadPageTitle);
  $downloadPageUrl = get_page_link($downloadPage->ID);

  $xml .=
      '<latest-version>' . $latestVersion . '</latest-version>
      <download-page-url>' . $downloadPageUrl . '</download-page-url>
    </application-info>';

  print($xml);
?>
