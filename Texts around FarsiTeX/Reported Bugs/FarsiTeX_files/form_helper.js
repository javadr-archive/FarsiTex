function FormHelper(theForm) {
    this.addBrackets = function() {
        for (var i=0; i<theForm.elements.length;i++) {
            var inputTag = theForm.elements[i];
            if (inputTag.name && inputTag.type != 'file') {
                inputTag.name += '[]';
            }
        }
    }

    this.removeBrackets = function() {
        for (var i=0; i<theForm.elements.length;i++) {
            var inputTag = theForm.elements[i];
            if (inputTag.name && inputTag.type != 'file' && inputTag.name.match(/\[\]$/)) {
                inputTag.name = inputTag.name.replace(/\[\]$/, '');
            }
        }
    }
}