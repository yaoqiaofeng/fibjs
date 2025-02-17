var test = require("test");
test.setup();

var fs = require('fs');
var path = require('path');
var zip = require('zip');
var io = require('io');
var http = require('http');
var coroutine = require('coroutine');

var vmid = require('coroutine').vmid;
var pathname = path.join(__dirname, 'test_dir' + vmid);

var ms = new io.MemoryStream();
var ms1 = new io.MemoryStream();

describe("zip", () => {
    var zipfile;
    var file;
    var efile1,
        efile2,
        efile3;
    before(() => {
        if (!fs.exists(pathname)) {
            fs.mkdir(pathname);
        }
    });
    after(() => {
        if (efile1)
            fs.unlink(efile1);

        if (efile2)
            fs.unlink(efile2);

        if (efile3)
            fs.unlink(efile3);

        if (fs.exists(path.join(__dirname, 'unzip_test.js.extract')))
            fs.unlink(path.join(__dirname, 'unzip_test.js.extract'));

        if (fs.exists(path.join(__dirname, 'unzip_test.zip' + vmid)))
            fs.unlink(path.join(__dirname, 'unzip_test.zip' + vmid));

        if (fs.exists(pathname))
            fs.rmdir(pathname);

        ms.close();
        ms1.close();
    });
    afterEach(() => {
        if (zipfile) {
            zipfile.close();
            zipfile = null;
        }
        if (file) {
            file.close();
            file = null;
        }
    })

    it("write file to zip", () => {
        zipfile = zip.open(path.join(__dirname, 'unzip_test.zip' + vmid), "w");
        zipfile.write(path.join(__dirname, 'unzip_test.js'), 'unzip_test.js');
        zipfile.close();

        zipfile = zip.open(path.join(__dirname, 'unzip_test.zip' + vmid));

        assert.equal('unzip_test.js', zipfile.namelist()[0]);
    });

    it("is zip file", () => {
        assert.equal(zip.isZipFile(path.join(__dirname, 'unzip_test.js')), false);
        assert.equal(zip.isZipFile(path.join(__dirname, 'unzip_test.zip' + vmid)), true);
    });

    it("zip filename in unicode", () => {
        var fname = "测试.zip" + vmid;
        var f = zip.open(path.join(__dirname, fname), "w");
        f.write(path.join(__dirname, 'unzip_test.js'), 'unzip_test.js');
        f.close();
        assert.equal(zip.isZipFile(path.join(__dirname, fname)), true);
        fs.unlink(path.join(__dirname, fname));
    })

    it("namelist & infolist & getinfo", () => {
        zipfile = zip.open(path.join(__dirname, 'unzip_test.zip' + vmid));
        var namelist = zipfile.namelist();
        var infolist = zipfile.infolist();
        var info = zipfile.getinfo("unzip_test.js")

        assert.equal(namelist[0], "unzip_test.js");

        assert.equal(infolist.length, 1);
        assert.equal(infolist[0].file_size, fs.stat(path.join(__dirname, "unzip_test.js")).size);
        assert.equal(infolist[0].filename, fs.stat(path.join(__dirname, "unzip_test.js")).name);
        assert.equal(infolist[0].password, false);
        assert.equal(infolist[0].compress_type, "Deflate");

        assert.equal(infolist[0].password, info.password);
        assert.equal(infolist[0].compress_type, info.compress_type);
        assert.equal(infolist[0].filename, info.filename);
        assert.equal(infolist[0].file_size, info.file_size);
        assert.equal(infolist[0].date.getTime(), info.date.getTime());

        assert.notLessThan(new Date().getTime() - info.date.getTime(), 0);
        assert.lessThan(new Date().getTime() - info.date.getTime(), 60000);
    });

    it("open zip file & read", () => {
        zipfile = zip.open(path.join(__dirname, 'unzip_test.zip' + vmid));
        var buf = zipfile.read('unzip_test.js');

        file = fs.openFile(path.join(__dirname, 'unzip_test.js'));
        var buf1 = file.readAll();

        assert.deepEqual(buf, buf1);
    });

    it("open zip buffer & read", () => {
        file = fs.openFile(path.join(__dirname, 'unzip_test.zip' + vmid));
        var buf = file.readAll();
        file.close();

        zipfile = zip.open(buf);
        buf = zipfile.read('unzip_test.js');

        file = fs.openFile(path.join(__dirname, 'unzip_test.js'));
        var buf1 = file.readAll();

        assert.deepEqual(buf, buf1);
    });

    it("open zip stream & read", () => {
        file = fs.openFile(path.join(__dirname, 'unzip_test.zip' + vmid));
        var buf = file.readAll();
        ms.write(buf);
        ms.rewind();
        file.close();

        zipfile = zip.open(ms);
        buf = zipfile.read('unzip_test.js');

        file = fs.openFile(path.join(__dirname, 'unzip_test.js'));
        var buf1 = file.readAll();

        assert.deepEqual(buf, buf1);
    });

    it("write buffer & stream to zip", () => {
        zipfile = zip.open(path.join(__dirname, 'unzip_test.zip' + vmid), "w");
        file = fs.openFile(path.join(__dirname, 'unzip_test.js'));

        var buf = file.readAll();
        zipfile.write(buf, 'unzip_test.js.bak');

        var rep = new http.Request();
        rep.body.write("0123456789");

        rep.sendTo(ms1);
        ms1.rewind();

        zipfile.write(ms1, "http.rq");
        zipfile.close();

        zipfile = zip.open(path.join(__dirname, 'unzip_test.zip' + vmid));
        var buf2 = zipfile.read('unzip_test.js.bak');

        assert.deepEqual(buf, buf2);

        buf2 = zipfile.read('http.rq');
        assert.equal(buf2.toString(), 'GET / HTTP/1.1\r\nConnection: keep-alive\r\nContent-Length: 10\r\n\r\n0123456789');
    });

    it("readall in zip", () => {
        zipfile = zip.open(path.join(__dirname, 'unzip_test.zip' + vmid));
        var datas = zipfile.readAll();

        file = fs.openFile(path.join(__dirname, 'unzip_test.js'));
        var buf = file.readAll();

        assert.equal(datas[0].data.length, buf.length);
        assert.equal(datas[0].data.toString(), buf.toString());
        assert.equal(datas[0].file_size, buf.length);
        assert.equal(datas[0].filename, "unzip_test.js.bak");

        ms1.rewind();
        buf = ms1.read();
        assert.deepEqual(datas[1].data, buf);
        assert.equal(datas[1].file_size, buf.length);
        assert.equal(datas[1].filename, "http.rq");
    });

    it("extract zip to file", () => {
        zipfile = zip.open(path.join(__dirname, 'unzip_test.zip' + vmid));
        zipfile.extract('unzip_test.js.bak', path.join(__dirname, 'unzip_test.js.extract'));

        file = fs.openFile(path.join(__dirname, 'unzip_test.js.extract'));
        var buf = file.readAll();
        file.close();
        file = fs.openFile(path.join(__dirname, 'unzip_test.js'));
        var buf1 = file.readAll();

        assert.deepEqual(buf, buf1);
    });

    it("extract zip to stream", () => {
        zipfile = zip.open(path.join(__dirname, 'unzip_test.zip' + vmid));
        var stream = new io.MemoryStream();
        zipfile.extract('unzip_test.js.bak', stream);

        stream.rewind();
        file = fs.openFile(path.join(__dirname, 'unzip_test.js'));
        var buf = file.readAll();
        var buf1 = stream.read();

        assert.deepEqual(buf, buf1);
    });

    it("extract all in zip", () => {
        zipfile = zip.open(path.join(__dirname, 'unzip_test.zip' + vmid));

        zipfile.extractAll(pathname);

        efile1 = pathname + '/unzip_test.js.bak';
        efile2 = pathname + '/http.rq';

        assert.equal(fs.exists(efile1), true);
        assert.equal(fs.exists(efile2), true);

        assert.equal(fs.readTextFile(efile1), fs.readTextFile(path.join(__dirname, 'unzip_test.js')));
        assert.equal(fs.readTextFile(efile2), 'GET / HTTP/1.1\r\nConnection: keep-alive\r\nContent-Length: 10\r\n\r\n0123456789');
    });

    it("write file append to zip", () => {
        zipfile = zip.open(path.join(__dirname, 'unzip_test.zip' + vmid), 'a');
        var buf = new Buffer('hello world');
        zipfile.write(buf, 'buf.txt');
        zipfile.close();

        zipfile = zip.open(path.join(__dirname, 'unzip_test.zip' + vmid));
        assert.equal(zipfile.read('buf.txt').toString(), 'hello world');
    });

    it("read and write with password", () => {
        var password = "1234";
        zipfile = zip.open(path.join(__dirname, 'unzip_test.zip' + vmid), 'a');
        var buf = new Buffer('password test');
        zipfile.write(buf, 'password.txt', password);
        zipfile.close();

        zipfile = zip.open(path.join(__dirname, 'unzip_test.zip' + vmid));
        assert.equal(zipfile.read('password.txt', password).toString(), 'password test');
    })

    if (Buffer.isEncoding("gbk"))
        it("zip with codec", () => {
            zipfile = zip.open(path.join(__dirname, 'unzip_test.zip' + vmid), 'w', "gbk");
            var buf = new Buffer('codec test');
            zipfile.write(buf, '密码.txt');
            zipfile.close();

            zipfile = zip.open(path.join(__dirname, 'unzip_test.zip' + vmid), "r", "gbk");
            assert.equal('密码.txt', zipfile.namelist()[0]);
            assert.equal('密码.txt', zipfile.infolist()[0].filename);
            assert.equal('密码.txt', zipfile.getinfo('密码.txt').filename);
            assert.equal(zipfile.read('密码.txt').toString(), 'codec test');
            assert.equal(zipfile.readAll()[0].filename, '密码.txt');

            zipfile.extractAll(pathname);
            efile3 = pathname + '/密码.txt';
            assert.equal(fs.exists(efile3), true);
        })

    it("bugfix: read from empty file", () => {
        zip.open(new io.MemoryStream());
    });
});

require.main === module && test.run(console.DEBUG);