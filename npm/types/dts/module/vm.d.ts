/// <reference path="../_import/_fibjs.d.ts" />
/// <reference path="../interface/SandBox.d.ts" />
/**
 * @description 沙箱模块，用于隔离不同安全等级的运行环境
 * 
 *  通过建立隔离沙箱，可以限制脚本运行时可以接触的资源，隔离不同脚本执行环境，并可以为不同的环境定制基础模块，以保障整体运行环境的安全。
 * 
 *  下面的示例创建一个沙箱，限制只允许访问全局基础模块中的 assert 模块，并添加 a 和 b 两个定制模块：
 *  ```JavaScript
 *  var vm = require('vm');
 *  var sbox = new vm.SandBox({
 *    a: 100,
 *    b: 200,
 *    assert: require('assert')
 *  });
 * 
 *  var mod_in_sbox = sbox.require('./path/to/mod');
 *  ```
 *  
 */
declare module 'vm' {
    /**
     * @description 创建一个 SandBox 对象，参见 SandBox 
     */
    const SandBox: typeof Class_SandBox;

}

