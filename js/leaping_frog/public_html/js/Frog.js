FrogClass = Class.extend (
{
   id : "",
   
   pos : {
       x : 0,
       y : 0
   },
   
   sprites : {
       standing : [],
       leaping : []
   },
   
   curr_sprite : 0,
   leaping : false
});