function TrimValue(value)
	value=Trim(value)
	TrimValue=value
end function

function validate_email(Expression)
   	Dim objRegExp
   	Set objRegExp = New RegExp
   	objRegExp.Pattern = "^[\w-\.]{1,}\@([\da-zA-Z-]{1,}\.){1,}[\da-zA-Z-]{2,3}$"
   	validate_email = objRegExp.Test(Expression)
end function