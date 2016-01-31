/**
 * Editace klasifikace - prepinani vodorovneho/svisleho posunu TAB
 */
function ToggleTabIndex() {
	/*** inicializace ***/
	var buttonVertical = jQuery('#cs_vertical_tabindex');
	var buttonHorizontal = jQuery('#cs_horizontal_tabindex');

	var inputs = jQuery('#overTable tbody input');

	/* nastavime prepinaci tlacikta */
	buttonVertical.click(tabIndexVertical);
	buttonHorizontal.click(tabIndexHorizontal);

	/* vychozi tabindex je horizontalni (fce se pro zmateni soupere jmenuji opacne) */
	tabIndexHorizontal();

	/* nastaveni hoveru tr pro horizontalni posun */
	inputs.each(function(index, item) {
		jQuery(item).focus(function() {
			jQuery(item).parents('tr').addClass('hover');
		});
		jQuery(item).blur(function() {
			jQuery(item).parents('tr').removeClass('hover');
		});
	});

	/*** nastavi tabindexy pro vodorovny posun ***/
	function tabIndexHorizontal() {
		buttonVertical
			.addClass('disabled')
			.attr('disabled', 'disabled')
		;
		buttonHorizontal
			.addClass('disabled')
			.attr('disabled', 'disabled')
		;

		var tabIndex = 1;

		inputs.each(function (index, item) {
			if (jQuery(item).attr('name').match(/^cs_column/) && jQuery(item).attr('type') != 'hidden') {
				jQuery(item).attr('tabindex', tabIndex);
				tabIndex++;
			}
		});
		/* povolime tlacitka pro opacny smer posunu */
		buttonVertical
			.removeAttr('disabled')
			.removeClass('disabled')
		;
	}

	/*** nastavi tabindexy pro svisly posun ***/
	function tabIndexVertical() {
		buttonVertical
			.addClass('disabled')
			.attr('disabled', 'disabled')
		;
		buttonHorizontal
			.addClass('disabled')
			.attr('disabled', 'disabled')
		;

		var rows = jQuery('input[name="cs_row_count"]').val();
		var cols = jQuery('input[name="cs_column_count"]').val();
		var row = 0;
		var col = 0;

		inputs.each(function(index, item) {
			if(jQuery(item).attr('name').match(/^cs_column/) && jQuery(item).attr('type') != 'hidden') {
				tabIndex = row + (rows * col) + 1;
				jQuery(item).attr('tabindex', tabIndex);
				col++;
				if(col >= cols) {
					row++;
					col = 0;
				}
			}
		});

		/* povolime tlacitka pro opacny smer posunu */
		buttonHorizontal
			.removeAttr('disabled')
			.removeClass('disabled')
		;
	}
}

jQuery(document).ready(function() {
	if (jQuery('#cs_vertical_tabindex').length) {
		var ToggleDirection = new ToggleTabIndex();
	}
});
