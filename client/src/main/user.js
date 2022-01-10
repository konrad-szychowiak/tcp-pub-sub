class User {
    onData(data) {
        console.log('DATA: ' + data);
    }

    addAction(foo) {
        this.action = foo;
        return this
    }
}

export class Subscriber extends User {
}

export class Publisher extends User {
}

