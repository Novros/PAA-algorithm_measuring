function ToggleTabs() {
	/*** inicializace ***/
	jQuery('#cs_menu').removeClass('hidden');
	jQuery('.page div').each(function(index, item) {
		if(item.id.match(/^cs_.*_div$/) && jQuery(item).hasClass(''))
			jQuery(item).addClass('hidden')
	});
	getActiveDiv().removeClass('hidden');
	jQuery('#cs_menu .tab').click(toggle);

	function getActiveTab() {
		return jQuery('#cs_menu .tab.tabSel');
	}

	function getActiveDiv() {
		var a = jQuery('#cs_menu .tab.tabSel').attr('id');
		return jQuery('#' + a.slice(0,-4) + '_div');
	}

	function toggle() {
		/* deaktivujeme vsechny taby */
		jQuery('#cs_menu .tab').removeClass('tabSel');

		/* schovame vsechny panely */
		jQuery('.page div').each(function(index, item) {
			if(item.id.match(/^cs_.*_div$/))
				jQuery(item).addClass('hidden')
		});

		/* aktivujeme tab */
		jQuery(this).addClass('tabSel');
		/* zobrazime panel */
		getActiveDiv().removeClass('hidden');

		/* FIX obcas pri prechodu z na hodnoceni zustava hlavicka prilepena na vrsku viewport */
		jQuery('#overTable thead').removeClass('sticky');
		}
};

jQuery(document).ready(function() {
	if(jQuery('#cs_menu').length) {
		var ToggleEditTabs = new ToggleTabs();
	}
});
