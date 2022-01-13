type PackHead = { id: number } | { name: string }

/**
 * Custom protocol messages
 */
export class Pack {
  static del(id: number) {
    return `D\t${id};`;
  }

  static post(id: number, message: string) {
    return `P\t${id}\t${message};`;
  }

  static subscribe(id: number) {
    return `S\t${id};`
  }

  static unsubscribe(id: number) {
    return `U\t${id};`
  }
}