<?php

function yamoney_admin_settings(){
  $form = array();
  $form['yandex_all'] = array(
    '#type' => 'fieldset',
    '#title' => t('Base parameters'),
  );
  $form['yandex_all']['yandex_ip'] = array(
    '#type' => 'textfield',
    '#title' => t('Insert server IP'),
    '#default_value' => variable_get('yandex_ip', '0.0.0.0'),
  );
  $form['yandex_all']['yandex_mode'] = array(
    '#type' => 'select',
    '#title' => t('Select payment mode'),
    '#options' => array('test' => t('Test mode'), 'live' => t('Live mode')),
    '#default_value' => variable_get('yandex_mode', 'test'),
  );
  $form['yandex_all']['currency'] = array(
    '#markup' => '<b>'. t('Select the types of payments online') .'</b>',
  );
  $form['yandex_all']['yandex_payments_pc'] = array(
    '#type' => 'checkbox',
    '#title' => t('Yandex money'),
    '#default_value' => variable_get('yandex_payments_pc', 1),
  );
  $form['yandex_all']['yandex_payments_ac'] = array(
    '#type' => 'checkbox',
    '#title' => t('Credit card'),
    '#default_value' => variable_get('yandex_payments_ac', 1),
  );
  $form['yandex_all']['yandex_payments_gp'] = array(
    '#type' => 'checkbox',
    '#title' => t('Cash or terminal'),
    '#default_value' => variable_get('yandex_payments_gp', 1),
  );
  $form['yandex_all']['yandex_payments_mc'] = array(
    '#type' => 'checkbox',
    '#title' => t('Mobile phone'),
    '#default_value' => variable_get('yandex_payments_mc', 1),
  );
  $form['yandex_all']['yandex_payments_wm'] = array(
    '#type' => 'checkbox',
    '#title' => t('WebMoney'),
    '#default_value' => variable_get('yandex_payments_wm', 1),
  );
  $form['yandex_shop_setting'] = array(
    '#type' => 'fieldset',
    '#title' => t('Yandex shop settings'),
  );
  $form['yandex_shop_setting']['yandex_user_status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Select if you have a shop in Yandex'),
    '#description' => t('Select this checkbox only you have a shop in yandex money service.'),
    '#default_value' => variable_get('yandex_user_status', 0),
  );  
  $form['yandex_shop_setting']['yandex_shop'] = array(
    '#type' => 'textfield',
    '#title' => t('Shop ID.'),
    '#description' => t('You shop ID. If you have any shops in you yandex account'),
    '#default_value' => variable_get('yandex_shop', ''),
    '#size' => 2,
  );
  $form['yandex_shop_setting']['yandex_scid'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter Scid'),
    '#default_value' => variable_get('yandex_scid', ''),
    '#size' => 5,
  );
  $form['yandex_shop_setting']['yandex_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Shop security key.'),
    '#description' => t('You shop password security key. Not you payment password'),
    '#default_value' => variable_get('yandex_secret', ''),
    '#size' => 17,
  );

  $form['yandex_purse_setting'] = array(
    '#type' => 'fieldset',
    '#title' => t('Yandex purse settings'),
  );
  $form['yandex_purse_setting']['yandex_receiver'] = array(
    '#type' => 'textfield',
    '#title' => t('Purse number'),
    '#description' => t('Your yandex money purse number.'),
    '#default_value' => variable_get('yandex_receiver', ''),
    '#size' => 14,
  );    
  
  $form['yandex_purse_setting']['yandex_formcomment'] = array(
    '#type' => 'textfield',
    '#title' => t('Pay comment.'),
    '#description' => t('Your yandex money pay comment.'),
    '#default_value' => variable_get('yandex_formcomment', ''),
  );
  
  $form['yandex_texts'] = array(
    '#type' => 'fieldset',
    '#title' => t('Text for success and fail payment pages'),
  );
  $success = variable_get('yandex_success_text', '');
  $form['yandex_texts']['yandex_success_text'] = array(
    '#type' => 'text_format',
    '#title' => t('Text for success page'),
    '#default_value' => $success['value'] ? $success['value'] : '',
    '#format' => $success['format'] ? $success['format'] : '',
  );
  $fail = variable_get('yandex_fail_text', '');
  $form['yandex_texts']['yandex_fail_text'] = array(
    '#type' => 'text_format',
    '#title' => t('Text for fail page'),
    '#default_value' => $fail['value'] ? $fail['value'] : '',
    '#format' => $fail['format'] ? $fail['format'] : '',
  );
  return system_settings_form($form);
}

function yamoney_admin_settings_validate($form, &$form_state){
  if(!$form_state['values']['yandex_payments_pc'] && !$form_state['values']['yandex_payments_ac'] && !$form_state['values']['yandex_payments_gp'] && !$form_state['values']['yandex_payments_mc']) {
    form_set_error('yandex_payments_pc');
    form_set_error('yandex_payments_ac');
    form_set_error('yandex_payments_gp');
    form_set_error('yandex_payments_mc', t('You do not choose the type of payment online!'));
  }
  if($form_state['values']['yandex_ip']) {
    $check_ip = explode('.', $form_state['values']['yandex_ip']);
    foreach($check_ip as $item) {
      if(!is_numeric($item) || count($check_ip) > 4 || $item > 999) {
        form_set_error('yandex_ip', t('IP is not correct. Please insert correct server IP or insert 0.0.0.0 to default!'));
        break;
      }
    }
  }
  else {
    form_set_error('yandex_ip', t('IP is empty. Please insert yandex server IP or insert 0.0.0.0 to default!'));
  }
}