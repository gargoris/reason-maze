
type b;
type t = (int, int, b);
type size =  (int, int);

let vertex (x, y, w) => x + y * w;
let from_vertex v w => (v mod w, v / w);

let vertex_count (w, h) => w * h;

let adjacent_to x y w h => {
  let a = [];
  let a = x === 0 ? a : [vertex (x - 1, y, w), ...a];
  let a = y === 0 ? a : [vertex (x, y - 1, w), ...a];
  let a = x >= w - 1 ? a : [vertex (x + 1, y, w), ...a];
  let a = y >= h - 1 ? a : [vertex (x, y + 1, w), ...a];
  a;
};

let adjacency_list (w, h) => {
  let v = Array.make (w * h) [];
  for x in 0 to (w - 1) {
    for y in 0 to (h - 1) {
      Array.set v
        (vertex (x, y, w))
        (adjacent_to x y w h);
    }
  };
  v
};

type direction =
  | Up
  | Down
  | Left
  | Right;

let direction_to (x, y) (a, b) => {
  x === a - 1
    ? Left
    : (x === a + 1
       ? Right
       : (y === a - 1
          ? Up
          : (y === a + 1
             ? Down
             : Left)))
};

module Float = {
  let (+) t t' => t +. t';
  let (-) t t' => t -. t';
  let ( * ) t t' => t *. t';
};

let points_to_line p1 p2 (w, h) (wsize, hsize) => {
  let dx = wsize /. (float_of_int w);
  let dy = hsize /. (float_of_int h);
  let (x, y) = p1;
  let fx = float_of_int(x);
  let fy = float_of_int(y);
  open Float;

  let pts = switch (direction_to p1 p2) {
    | Up => ((fx * dx, fy * dy),
             ((fx + 1.0) * dx, fy * dy))
    | Down => ((fx * dx, (fy + 1.0) * dy),
               ((fx + 1.0) * dx, (fy + 1.0) * dy))
    | Left => ((fx * dx, fy * dy),
               (fx * dx, (fy + 1.0) * dy))
    | Right => (((fx + 1.0) * dx, fy * dy),
                ((fx + 1.0) * dx, (fy + 1.0) * dy))
  };
  Shared.Line pts
};

/*
let drawable_walls walls (w, h) osize => {
  List.map

  (fun (start, vend) => {
    points_to_line
      (from_vertex start w)
      (from_vertex vend w)
      (w, h) osize
  })
  walls
};
*/

let drawable_wall (start, vend) (w, h) osize => {
    points_to_line
      (from_vertex start w)
      (from_vertex vend w)
      (w, h) osize
};

