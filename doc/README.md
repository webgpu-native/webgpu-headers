Documentation
=============

The documentation of WebGPU native is automatically generated from `webgpu.yml` using Python and [MkDocs](https://www.mkdocs.org).

Build
-----

```bash
# 1. Install python dependencies (potentially in a virtualenv)
pip install -r requirements.txt

# 2. Generate doc source from webgpu.yml
(cd ..; make gen-docs)

# 3. Generate html doc from doc source
mkdocs build
```

The documentation is then available in `site/`.
