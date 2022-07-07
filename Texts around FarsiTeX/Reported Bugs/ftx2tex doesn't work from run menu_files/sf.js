var sf = {};
try{
    watch("sf", function(){alert("don't redefine me!")});
} catch(e) {
    //Do nothing cuz IE doesn't know about watch
}
