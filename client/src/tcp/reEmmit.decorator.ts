// todo docs
export function reEmmit(eventName: string, debug?: boolean) {
  return function (target: any, propertyKey: string, descriptor: PropertyDescriptor) {
    let originalMethod = descriptor.value;
    //wrapping the original method
    descriptor.value = function (...args: any[]) {
      const emitter = (this as any).wc
      let result = originalMethod.apply(this, args);
      emitter.send(eventName, result)
      return result;
    }
  }
}

