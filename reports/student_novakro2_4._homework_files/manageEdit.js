/**
 * Administrace klasifikace - potvrzovani prejmenovani a mazani sloupcu
 */
function ManageEdit() {
	/*** inicializace ***/
	/* zajistime submit na onChange vybranym elementum */
	if (jQuery('#cs_form_select')) {
		jQuery('#cs_lang_selector').change(submitOnChange);
		jQuery('#cs_type_selector').change(submitOnChange);
		jQuery('#cs_part_selector').change(submitOnChange);
	}

	if (jQuery('#cs_form_edit_cols')) {
		/* priprava inputu pro validaci */
		var form = jQuery('#cs_form_edit_cols');

		/* iterujeme vsechny inputy v tabulce a tridime si je do poli */
		var ids = form.find('input[name^="cs_name"]');
		var toDelete = form.find('input[name^="cs_del"]');
		var prevIds = form.find('input[name^="cs_name"]').map(function() { return this.value; });

		jQuery(form).submit(function(e) {
			if(!(valid = validateForm()))
				e.preventDefault();
			return valid;
		});
	}

	/*** ve validaci zkusime odeslat formular ***/
	function validateForm() {
		var checkDel = false;
		var checkRename = false;
		var allow = true;
		var delMsg = form.find('input[name=cs_confirm_del_msg]').val();
		var renameMsg = form.find('input[name=cs_confirm_rename_msg]').val();

		/* zjistujem zda chceme neco smazat */
		for(i = 0; i < toDelete.length; i++) {
			var _id = form.find('input[name="cs_name['+i+']"]').val();
			var _name = form.find('input[name="cs_caption['+i+']"]').val();
			if (jQuery(toDelete[i]).attr('checked') == 'checked') {
				checkDel = true;
				delMsg += '\n\ridentifikátor ' + _id;
				if (_name.trim() != '') {
					delMsg += ' (jméno: ' + _name + ')';
				}
			}
		}

		/* zjistujem zda nechceme prejmenovat identifikator */
		for(i = 0; i < ids.length; i++) {
			var _value = jQuery(ids[i]).val();
			var _name = form.find('input[name="cs_caption['+i+']"]').val();

			if (prevIds[i] && _value != prevIds[i] && !jQuery(ids[i]).attr('name') != 'cs_name_add[]') {
				checkRename = true;
				if (_value == '')
					renameMsg += '\n\rnová hodnota '+ prevIds[i] + ' nemůže být prázdná!';
				else
					renameMsg += '\n\r' + prevIds[i] + ' -> ' + _value;
			}
		}

		if (checkDel && !confirm(delMsg)) allow = false;
		if (checkRename && !confirm(renameMsg)) allow = false;
		return allow;
	}
	/*** vsem elementum v parametru nastavi na onChange submit formulare ve kterem se nachazeji ***/
	function submitOnChange() {
		jQuery(this).parents('form').submit();
	}
};

jQuery(document).ready(function() {
	if(jQuery('#cs_form_edit_cols').length || jQuery('#cs_form_select').length)
		var ManageTableEdit = new ManageEdit();
});
