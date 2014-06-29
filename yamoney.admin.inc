<?php

/**
 * @return array
 */
function yamoney_admin_settings() {
  $form = array();

  // General settings
  $form['yamoney_all'] = array(
    '#type' => 'fieldset',
    '#title' => t('Base options'),
  );
  $form['yamoney_all']['yamoney_ip'] = array(
    '#type' => 'textarea',
    '#title' => t('Allowed IPs for callbacks'),
    '#default_value' => variable_get('yamoney_ip', '0.0.0.0'),
    '#description' => t('The list of IP addresses which has access to payment callbacks. One per line.<br/>0.0.0.0 means allow from all.')
  );
  $form['yamoney_all']['yamoney_mode'] = array(
    '#type' => 'select',
    '#title' => t('Payment mode'),
    '#options' => array(
      'test' => t('Test mode'),
      'live' => t('Live mode')
    ),
    '#default_value' => variable_get('yamoney_mode', 'test'),
  );

  $form['yamoney_all']['yamoney_payment_method'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Enabled payment methods'),
    '#options' => yamoney_get_payment_methods(),
    '#default_value' => variable_get('yamoney_payment_method', array_keys(yamoney_get_payment_methods())),
  );

  $form['yamoney_all']['yamoney_default_payment_method'] = array(
    '#type' => 'radios',
    '#title' => t('Default payment method'),
    '#options' => yamoney_get_payment_methods(),
    '#default_value' => variable_get('yamoney_default_payment_method', YAMONEY_DEFAULT_PAYMENT_METHOD),
  );

  // Shop settings
  $shop_states = array(
    // Hide the settings when the Yandex shop checkbox is disabled.
    'invisible' => array(
      ':input[name="yamoney_shop"]' => array('checked' => FALSE),
    ),
  );
  $form['yamoney_shop_setting'] = array(
    '#type' => 'fieldset',
    '#title' => t('Yandex shop settings'),
  );
  $form['yamoney_shop_setting']['yamoney_shop'] = array(
    '#type' => 'checkbox',
    '#title' => t('Select if you have a shop in Yandex.Money'),
    '#default_value' => variable_get('yamoney_shop', 0),
  );
  $form['yamoney_shop_setting']['yamoney_shop_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Shop ID'),
    '#description' => t('You shop ID. If you have any shops in you Yandex account.'),
    '#default_value' => variable_get('yamoney_shop_id', ''),
    '#size' => 2,
    '#states' => $shop_states,
  );
  $form['yamoney_shop_setting']['yamoney_scid'] = array(
    '#type' => 'textfield',
    '#title' => t('Shop SCID'),
    '#default_value' => variable_get('yamoney_scid', ''),
    '#size' => 5,
    '#states' => $shop_states,
  );
  $form['yamoney_shop_setting']['yamoney_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Shop security key'),
    '#description' => t('You shop password security key. Not you payment password.'),
    '#default_value' => variable_get('yamoney_secret', ''),
    '#size' => 17,
    '#states' => $shop_states,
  );

  // Purse settings
  $form['yamoney_purse_setting'] = array(
    '#type' => 'fieldset',
    '#title' => t('Yandex purse settings'),
  );
  $form['yamoney_purse_setting']['yamoney_receiver'] = array(
    '#type' => 'textfield',
    '#title' => t('Purse number'),
    '#description' => t('Your Yandex.Money purse number.'),
    '#default_value' => variable_get('yamoney_receiver', ''),
    '#size' => 14,
  );

  $form['yamoney_purse_setting']['yamoney_formcomment'] = array(
    '#type' => 'textfield',
    '#title' => t('Pay comment'),
    '#description' => t('Your Yandex.Money pay comment.'),
    '#default_value' => variable_get('yamoney_formcomment', ''),
  );

  $form['yamoney_texts'] = array(
    '#type' => 'fieldset',
    '#title' => t('Text for success and fail payment pages'),
  );
  $success = variable_get('yamoney_success_text', '');
  $form['yamoney_texts']['yamoney_success_text'] = array(
    '#type' => 'text_format',
    '#title' => t('Text for success page'),
    '#default_value' => $success['value'] ? $success['value'] : '',
    '#format' => $success['format'] ? $success['format'] : '',
  );
  $fail = variable_get('yamoney_fail_text', '');
  $form['yamoney_texts']['yamoney_fail_text'] = array(
    '#type' => 'text_format',
    '#title' => t('Text for fail page'),
    '#default_value' => $fail['value'] ? $fail['value'] : '',
    '#format' => $fail['format'] ? $fail['format'] : '',
  );
  return system_settings_form($form);
}

/**
 * @param array $form
 * @param array $form_state
 */
function yamoney_admin_settings_validate($form, &$form_state) {
  if (!$form_state['values']['yamoney_payment_method']) {
    form_set_error('yamoney_payment_method', t('You do not choose the type of payment online!'));
  }

  if ($form_state['values']['yamoney_ip']) {
    $ips = explode("\n", $form_state['values']['yamoney_ip']);
    foreach ($ips as $ip) {
      $ip = trim($ip);
      if (empty($ip)) {
        continue;
      }
      if (!filter_var($ip, FILTER_VALIDATE_IP)) {
        form_set_error('yamoney_ip', t('IP is not correct: %ip.<br/>Please insert correct server IP or insert 0.0.0.0 to default!', array(
          '%ip' => $ip,
        )));
      }
    }
  }
}