module geometry

struct Rectangle {
    width: int,
    height: int
}

impl Rectangle {
    fn area(passt) {
        ret passt.width * passt.height
    }

    fn perimeter(passt) {
        ret 2 * (passt.width + passt.height)
    }
}

export { impl Rectangle }
