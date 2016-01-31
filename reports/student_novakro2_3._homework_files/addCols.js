/**
 * Administrace klasifikace - pridavani dalsich radku pro definici sloupcu klasifikace
 */
function AddCols() {
	/*** inicializace ***/
	var form = jQuery('#cs_form_edit_cols');
	/* pridame ovladani pro pridavani sloupecku */
	addColControl(jQuery(form).find('table tfoot tr'));

	/* naklonujem posledni radku, kde jsou inputy pro pridani sloupce */
	var sample = jQuery(form).find('table tbody tr').last().clone();

	/* posledni bunku vyprazdnimme */
	jQuery(sample).find('td').last().html('');

	/*** DOM pro ovladani pridavani sloupcu ***/
	function addColControl(tr) {
		var td = document.createElement('td');
		jQuery(td)
			.attr('colspan', 5)
			.attr('style', 'text-align: right')
		;

		var colCountLabel = document.createElement('label');
		jQuery(colCountLabel)
			.html('přidat sloupce')
			.attr('for', 'colCount')
		;

		var colCount = document.createElement('input');
		jQuery(colCount)
			.attr('type', 'text')
			.attr('id', 'colCount')
			.attr('size', 1)
			.val(1)
			.keydown(function(event) {
				if (event.key == 'Enter') {
					event.stopPropagation();
					recountCols();
				}
			})
		;

		var addColsBtn = document.createElement('input');
		jQuery(addColsBtn)
			.attr('type', 'button')
			.attr('id', 'addCols')
			.val('upravit')
			.click(function() {
				recountCols();
			})
		;

		jQuery(td)
			.append(colCountLabel)
			.append(colCount)
			.append(addColsBtn)
		;

		jQuery(tr).find("td").attr('colspan', 2);
		jQuery(tr).append(td);
	}

	/*** pridavame naklonovanou posledni radku tabulky ***/
	function recountCols() {
		var polozek = jQuery('#colCount').val();
		if (polozek > 100) {
			alert("Nelze přidat najednou více jak 100 položek");
		} else {
			for (i = 0; i < polozek; i++) {
				var newCol = sample.clone()
				jQuery(form).find('tr').last().after(newCol);

				/* do posledni bunky vlozime misto textu tlacitko pro odebrani sloupce */

				var buttonOdebrat = document.createElement('input');
				jQuery(buttonOdebrat)
					.attr('type', 'button')
					.attr('title', 'odstranit sloupec')
					.val('X')
					.click(function() {
						jQuery(this).parents('tr').remove();
					})
				;
				jQuery(newCol).find('td').last().append(buttonOdebrat);
			}
		}
	}
};

/*** registrace ***/
jQuery(document).ready(function() {
	if(jQuery('#cs_form_edit_cols').length) {
		var AdminAddCols = new AddCols();
	}
});
