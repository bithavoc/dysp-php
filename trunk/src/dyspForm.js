function dysp_submitFormArgs(formId,controlId,postName,postArg)
{
	var form = document.getElementById(formId);
	form.elements.formName.value =formId;
	form.elements.postName.value =postName;
	form.elements.postArg.value =postArg;
	form.elements.controlId.value =controlId;
	form.submit();
}