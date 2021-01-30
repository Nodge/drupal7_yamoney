<?php
/**
 * @return array
 */
function yamoney_admin_settings() {
	global $base_url;
	$path = drupal_get_path('module', 'yamoney') . '/' . 'yamoney.info';
	$info = drupal_parse_info_file($path);

	$form = array();
	$form['yamoney_all'] = array(
		'#type' => 'fieldset',
		'#description' => t('Работая с модулем, вы автоматически соглашаетесь с <a href="https://money.yandex.ru/doc.xml?id=527132" target="_blank">условиями его использования</a>.'),
		'#weight' => 10,
	);
	$form['yamoney_all']['lbl_version'] = array(
		'#markup' => t('Version: ').$info['version'],
	);
	$form['yamoney_all']['yamoney_ip'] = array(
		'#type' => 'hidden',
		'#title' => t('Allowed IPs for callbacks'),
		'#default_value' => variable_get('yamoney_ip', '0.0.0.0'),
		'#description' => t('The list of IP addresses which has access to payment callbacks. One per line.<br/>0.0.0.0 means allow from all.')
	);

	$form['vertical_tabs'] = array(
		'#type' => 'vertical_tabs',
		'#weight' => 20,
	);
	$form['yamoney_kassa_tab'] = array(
		'#type' => 'fieldset',
		'#title' => t('Yandex.Kassa'),
		//'#description' => t('<p>Для работы с модулем нужно подключить магазин к <a target="_blank" href="https://kassa.yandex.ru/">Яндекс.Кассе</a>.</p>'),
		'#group' => 'vertical_tabs',
		'#weight' => 10,
	);
	$form['yamoney_kassa_tab']['intro'] = array(
		'#markup' => t('Для работы с модулем нужно подключить магазин к <a target="_blank" href="https://kassa.yandex.ru/">Яндекс.Кассе</a>.'),
	);
	$form['yamoney_kassa_tab']['yamoney_shop'] = array(
		'#type' => 'checkbox',
		'#title' => t('Включить приём платежей через Яндекс.Кассу'),
		'#attributes' => array('id'=>'kassa-checkbox'),
		'#default_value' => variable_get('yamoney_shop', 0),
	);
	$form['yamoney_kassa_tab']['yamoney_mode'] = array(
		'#type' => 'radios',
		'#options' => array(
			'test' => t('Test mode'),
			'live' => t('Live mode')
		),
		'#default_value' => variable_get('yamoney_mode', 'test'),
	);
	$form['yamoney_kassa_tab']['lbl_checkUrl'] = array(
		'#type' => 'textfield',
		'#title' => t('checkUrl'),
		'#attributes' => array('disabled'=>'disabled'),
		'#default_value' => url('yamoney/check_order', array('absolute' => TRUE)),
		'#description' => t('Скопируйте эту ссылку в поле Check URL в настройках личного кабинета Яндекс.Кассы'),
	);
	$form['yamoney_kassa_tab']['lbl_avisoUrl'] = array(
		'#type' => 'textfield',
		'#title' => t('avisoUrl'),
		'#attributes' => array('disabled'=>'disabled'),
		'#default_value' => url('yamoney/check_payment', array('absolute' => TRUE)),
		'#description' => t('Скопируйте эту ссылку в поле Aviso URL в настройках личного кабинета Яндекс.Кассы'),
	);
	$form['yamoney_kassa_tab']['lbl_successUrl'] = array(
		'#type' => 'textfield',
		'#title' => t('successUrl/failUrl'),
		'#attributes' => array('disabled'=>'disabled'),
		'#default_value' => t('Страницы с динамическими адресами'),
		'#description' => t('Включите «Использовать страницы успеха и ошибки с динамическими адресами» в настройках личного кабинета Яндекс.Кассы'),
	);
	$form['yamoney_kassa_tab']['lbl_setting'] = array(
		'#markup' => t('<h3>Shop setting</h3>'),
	);
	$form['yamoney_kassa_tab']['yamoney_shop_id'] = array(
		'#type' => 'textfield',
		'#title' => t('Shop ID'),
		'#description' => t('Идентификатор магазина'),
		'#default_value' => variable_get('yamoney_shop_id', ''),
		'#size' => 2,
	);
	$form['yamoney_kassa_tab']['yamoney_scid'] = array(
		'#type' => 'textfield',
		'#title' => t('Scid'),
		'#description' => t('Номер витрины магазина'),
		'#default_value' => variable_get('yamoney_scid', ''),
		'#size' => 5,
	);
	$form['yamoney_kassa_tab']['yamoney_secret'] = array(
		'#type' => 'textfield',
		'#title' => t('ShopPassword'),
		'#description' => t('Секретное слово'),
		'#default_value' => variable_get('yamoney_secret', ''),
		'#size' => 17,
	);
	$form['yamoney_kassa_tab']['lbl_setting_end'] = array(
		'#markup' => t("Shop ID, scid, ShopPassword можно посмотреть в <a href='https://money.yandex.ru/my' target='_blank'>личном кабинете</a> после подключения Яндекс.Кассы."),
	);
	$form['yamoney_kassa_tab']['lbl_paymode'] = array(
		'#markup' => t('<h3>Настройка сценария оплаты</h3>'),
	);
	$paymode_states = array(
		'invisible' => array(
			':input[name="yamoney_paymode"]' => array('value' => 'kassa'),
		),
	);
	$form['yamoney_kassa_tab']['yamoney_paymode'] = array(
		'#type' => 'select',
		'#title' => t('Payments mode'),
		'#options' => array(
			'kassa' => t('Kassa mode'),
			'shop' => t('Shop mode')
		),
		'#default_value' => variable_get('yamoney_paymode', 'kassa'),
	);
	/*$form['yamoney_kassa_tab']['yamoney_paylogo'] = array(
		'#type' => 'checkbox',
		'#title' => t('Use logo of payment button'),
		'#default_value' => variable_get('yamoney_paylogo', 1),
		'#states' => array(
			'invisible' => array(
				':input[name="yamoney_paymode"]' => array('value' => 'shop'),
			),
		),
	);*/
	$form['yamoney_kassa_tab']['yamoney_payment_method'] = array(
		'#type' => 'checkboxes',
		'#title' => t('Enabled payment methods'),
		'#options' => yamoney_get_payment_methods(),
		'#default_value' => variable_get('yamoney_payment_method', array_keys(yamoney_get_payment_methods())),
		'#states' => $paymode_states,
	);

	$form['yamoney_kassa_tab']['yamoney_default_payment_method'] = array(
		'#type' => 'radios',
		'#title' => t('Default payment method'),
		'#options' => yamoney_get_payment_methods(),
		'#default_value' => variable_get('yamoney_default_payment_method', YAMONEY_DEFAULT_PAYMENT_METHOD),
		'#states' => $paymode_states,
	);

    /*********** tax edit****************/

    if (module_exists('commerce_tax') && module_exists('commerce_tax_ui')) {
        $form['yamoney_kassa_tab']['yamoney_send_check'] = array(
            '#type' => 'radios',
            '#title' => t('Отправлять в Яндекс.Кассу данные для чеков (54-ФЗ)'),
            '#options' => array(
                '1' => t('Включить'),
                '0' => t('Выключить')
            ),
            '#description' => 'Отправлять в Яндекс.Кассу данные для чеков (54-ФЗ) НДС',
            '#default_value' => variable_get('yamoney_send_check', '0'),
        );

        $taxes = commerce_tax_ui_commerce_tax_rate_info();

        foreach ($taxes as $tax) {
            $form['yamoney_kassa_tab']['yamoney_kassa_tax_' . $tax['name']] = array(
                '#type' => 'select',
                '#title' => $tax['title'] . ' ' . t('Передавать в Яндекс.Кассу как'),
                '#options' => array(
                    1 => t('Без НДС'),
                    2 => t('0%'),
                    3 => t('10%'),
                    4 => t('18%'),
                    5 => t('Расчётная ставка 10/110'),
                    6 => t('Расчётная ставка 18/118'),
                ),
                '#default_value' => variable_get('yamoney_kassa_tax_' . $tax['name'], 1),
                '#description' => 'Слева — ставка НДС в вашем магазине, справа — в Яндекс.Кассе. Пожалуйста, сопоставьте их.',
                '#states' => array(
                    'invisible' => array(
                        ':input[name="yamoney_send_check"]' => array('value' => '0'),
                    ),
                )
            );
        }
    }

    /*********** tax edit****************/

    if (module_exists('uc_taxes')) {
        $form['yamoney_kassa_tab']['yamoney_send_check'] = array(
            '#type' => 'radios',
            '#title' => t('Отправлять в Яндекс.Кассу данные для чеков (54-ФЗ)'),
            '#options' => array(
                '1' => t('Включить'),
                '0' => t('Выключить')
            ),
            '#description' => 'Отправлять в Яндекс.Кассу данные для чеков (54-ФЗ) НДС',
            '#default_value' => variable_get('yamoney_send_check', '0'),
        );

        $taxes = uc_taxes_rate_load();

        foreach ($taxes as $tax) {
            $form['yamoney_kassa_tab']['yamoney_kassa_tax_' . $tax->id] = array(
                '#type' => 'select',
                '#title' => $tax->name . ' ' . t('Передавать в Яндекс.Кассу как'),
                '#options' => array(
                    1 => t('Без НДС'),
                    2 => t('0%'),
                    3 => t('10%'),
                    4 => t('18%'),
                    5 => t('Расчётная ставка 10/110'),
                    6 => t('Расчётная ставка 18/118'),
                ),
                '#default_value' => variable_get('yamoney_kassa_tax_' . $tax->id, 1),
                '#description' => 'Слева — ставка НДС в вашем магазине, справа — в Яндекс.Кассе. Пожалуйста, сопоставьте их.',
                '#states' => array(
                    'invisible' => array(
                        ':input[name="yamoney_send_check"]' => array('value' => '0'),
                    ),
                )
            );
        }
    }

    /*********** tax edit****************/

	/* ---- */
	$form['yamoney_p2p_tab'] = array(
		'#type' => 'fieldset',
		'#title' => t('Yandex.Money'),
		'#group' => 'vertical_tabs',
		'#weight' => 30,
	);
	$form['yamoney_p2p_tab']['intro'] = array(
		//'#markup' => t('Для работы с модулем нужно <a href="https://money.yandex.ru/new" target="_blank">открыть кошелек</a> на Яндексе и <a href="https://sp-money.yandex.ru/myservices/online.xml" target="_blank">зарегистрировать приложение</a> на сайте Яндекс.Денег'),
	);
	$form['yamoney_p2p_tab']['yamoney_p2p'] = array(
		'#type' => 'checkbox',
		'#attributes' => array('id'=>'p2p-checkbox'),
		'#title' => t('Включить прием платежей в кошелек на Яндексе'),
		'#default_value' => variable_get('yamoney_p2p', 0),
	);
	$form['yamoney_p2p_tab']['lbl_redirectUrl'] = array(
		'#type' => 'textfield',
		'#title' => t('RedirectURL'),
		'#attributes' => array('disabled'=>'disabled'),
		'#default_value' => url('yamoney/check_wallet', array('absolute' => TRUE)),
		'#description' => t("Скопируйте эту ссылку в верхнее поле на <a href='https://sp-money.yandex.ru/myservices/online.xml' target='_blank'>странице HTTP-уведомлений</a>"),
	);
	$form['yamoney_p2p_tab']['lbl_setting'] = array(
		'#markup' => t('<h3>Настройки приема платежей</h3>'),
	);
	$form['yamoney_p2p_tab']['yamoney_receiver'] = array(
		'#type' => 'textfield',
		'#title' => t('Purse number'),
		'#description' => t('Your Yandex.Money purse number.'),
		'#default_value' => variable_get('yamoney_receiver', ''),
		'#size' => 14,
		//'#states' => $p2p_states,
	);
    $form['yamoney_p2p_tab']['yamoney_secret'] = array(
        '#type' => 'textfield',
        '#title' => t('Секретное слово'),
        '#description' => t('Секретное слово'),
        '#default_value' => variable_get('yamoney_secret', ''),
        '#size' => 17,
    );
	$form['yamoney_p2p_tab']['yamoney_formcomment'] = array(
		'#type' => 'textfield',
		'#title' => t('Pay comment'),
		'#description' => t('Это название увидит пользователь'),
		'#default_value' => variable_get('yamoney_formcomment', $base_url),
		//'#states' => $p2p_states,
	);

	// footer settings
	$form['yamoney_texts'] = array(
		'#type' => 'fieldset',
		'#title' => t('Text for success and fail payment pages'),
		'#weight' => 40,
	);
	$success = variable_get('yamoney_success_text', array('value' => '', 'format' => ''));
	$form['yamoney_texts']['yamoney_success_text'] = array(
		'#type' => 'text_format',
		'#title' => t('Text for success page'),
		'#default_value' => $success['value'] ? $success['value'] : '',
		'#format' => $success['format'] ? $success['format'] : '',
	);
	$fail = variable_get('yamoney_fail_text', array('value' => '', 'format' => ''));
	$form['yamoney_texts']['yamoney_fail_text'] = array(
		'#type' => 'text_format',
		'#title' => t('Text for fail page'),
		'#default_value' => $fail['value'] ? $fail['value'] : '',
		'#format' => $fail['format'] ? $fail['format'] : '',
	);
	$form['#submit'][]='send_statistics';
	return system_settings_form($form);
}
/**
 * @param array $form
 * @param array $form_state
 */
function send_statistics($form, &$form_state) {
	global $base_url;
	$path = drupal_get_path('module', 'yamoney') . '/' . 'yamoney.info';
	$info = drupal_parse_info_file($path);
	$headers = array();
	$headers[] = 'Content-Type: application/x-www-form-urlencoded';
	$form_data=$form_state['input'];
	$array = array(
		'url' => $base_url,
		'cms' => 'drupal',
		'version' => VERSION,
		'ver_mod' => $info['version'],
		'yacms' => false,
		'email' => variable_get('site_mail', ''),
		'shopid' => (isset($form_data['yamoney_shop_id']))?$form_data['yamoney_shop_id']:0,
		'settings' => array(
			'kassa' => (isset($form_data['yamoney_shop']))?true:false,
			'kassa_epl' => (isset($form_data['yamoney_paymode']) && $form_data['yamoney_paymode'] =='kassa')?true:false,
			'p2p' => (isset($form_data['yamoney_shop']))?false:true
		)
	);
	$array_crypt = base64_encode(serialize($array));

	$url = 'https://statcms.yamoney.ru/v2/';
	$curlOpt = array(
		CURLOPT_HEADER => false,
		CURLOPT_RETURNTRANSFER => true,
		CURLOPT_SSL_VERIFYPEER => false,
		CURLOPT_SSL_VERIFYHOST => false,
		CURLINFO_HEADER_OUT => true,
		CURLOPT_POST => true,
	);

	$curlOpt[CURLOPT_HTTPHEADER] = $headers;
	$curlOpt[CURLOPT_POSTFIELDS] = http_build_query(array('data' => $array_crypt, 'lbl'=>1));

	$curl = curl_init($url);
	curl_setopt_array($curl, $curlOpt);
	$rbody = curl_exec($curl);
	$errno = curl_errno($curl);
	$error = curl_error($curl);
	$rcode = curl_getinfo($curl, CURLINFO_HTTP_CODE);
	curl_close($curl);
}
/**
 * @param array $form
 * @param array $form_state
 */
function yamoney_admin_settings_validate($form, &$form_state) {
	$checkboxs = $form_state['values']['yamoney_payment_method'];
	$d = array_count_values(array_values($checkboxs));
	if (count($checkboxs) == $d['0'] && isset($form_state['values']['yamoney_paymode']) && $form_state['values']['yamoney_paymode'] =='shop') {
		form_set_error('yamoney_payment_method', t('You do not choose the type of payment online!'));
	}
	if ($form_state['values']['yamoney_shop'] == $form_state['values']['yamoney_p2p'] && $form_state['values']['yamoney_shop']){
		$form_state['values']['yamoney_shop']=1;
		$form_state['values']['yamoney_p2p']=0;
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