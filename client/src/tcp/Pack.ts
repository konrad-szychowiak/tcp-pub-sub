import Buffer from "buffer";

type PackHead = { id: number } | { name: string }

/**
 * Custom protocol package object
 */
export class Pack {
  private constructor(readonly symbol: string, head: PackHead, tail: string[]) {
  }

  /**
   * Parse data buffer and run an appropriate protocol action
   * @param buffer
   */
  static fromBuffer(buffer: Buffer) {
  }

  toBuffer()
  // todo
  // : Buffer
  // Convert the package into socket-transferable buffer.
  {
  }
}