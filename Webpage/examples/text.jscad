// title      : Vector Text Rendering
// author     : Rene K. Mueller
// license    : MIT License
// description: playing with vector font
// date       : 2013/04/22
// file       : text.jscad

function getParameterDefinitions() {
   return [
      { name: 's', initial: "Lulu", type: 'text', caption: 'Text to render', size: 20 },
   ];
}

function main(param) {
   var o = [];

   var l = vector_text(0, 0, param.s);      // get line segments [ [ [x1,y1], [x2,y2] ...], [ ]... ]

   l.forEach(function(s) {                // process the line segments
      o.push(rectangular_extrude(s, { w:3, h:3 }));
   });


   return union(o).scale(1).translate([-200, 0, 0]);
}
