#include <babylon/misc/texture_tools.h>

#include <babylon/engines/engine.h>
#include <babylon/engines/scene.h>
#include <babylon/materials/effect.h>
#include <babylon/materials/textures/internal_texture.h>
#include <babylon/materials/textures/render_target_texture.h>
#include <babylon/materials/textures/texture.h>
#include <babylon/postprocesses/pass_post_process.h>
#include <babylon/postprocesses/post_process_manager.h>

namespace BABYLON {

std::string TextureTools::_environmentBRDFBase64Texture
  = "data:image/"
    "png;base64,"
    "iVBORw0KGgoAAAANSUhEUgAAAQAAAAEACAYAAABccqhmAAAgAElEQVR4Xu19Z7PtTHbW1g3jMM"
    "bGmGDAZAMm5xxMLDAU0WSKWOQcCoqccw6eGdtgk4yNbZxnvvAL+Af8Af6AsQl+"
    "06ako9X36dXPSi3pnPu+cz/cOntL3S1pq5+w1mrpLs/eud9fvn27rf9evPPwFz+v22S7fGZ/"
    "n7/70G79J5/Xv/qzbLP+Pnvvoc/6Tz7jX/15/c62LfeH7fofbpfP3l/"
    "ct36Wf+u4+D37+XYb++G26LPsr/zFttnPuh37bm1bt0f7MvtlnOx4uv0H4fty8UUsz77rfn/"
    "57u32cgXvDv72eQf0tl0+G38b0Nf9K4Dl704MEfA16KsE8Gw9JgD+"
    "DQE8EA0DT2b7GwK4GHnF4a8iguXZt9/vL5/dbisJbEq/uwD5vIK/fbbAv4N9U/"
    "8nJIDNCazKvBLBGwdwu62OhajxmQSAx6gqNp5HCg9wPan2nwSNjhLD8ux/"
    "3u8vP3y7vbwDAYjtR8AzFyDqLu1Q+YEINnew23rPCYiKb+q/K7o4AVT4tg0t/h4ydJZfkQASQ/"
    "d5b9fZ/Z1ENmuPn/cwYCYEELBguKC3nRkCnE0AFOwOKCOAR/sH/L4hgFMpbSWP5dn/"
    "uN9ffs7t9mJ5cAHoBLTyszBAFJ/F/"
    "xIKdASw5wgaEWDMLySxAk4svf6L+4QAGPiJCziNAPb4f3UZ2dh/"
    "m+z7BK4SAPYrxf5FB6ABPgCUAfANAZwKyscc7IEA/vv9/"
    "uLzbreXzx9cQCMACAl00m8jAlF7ov6SCMQ8gJsMFFBnCECSg5H6TxJAU3vPAbwhgFfz9AABeOE"
    "DBcIbB3AqPzwQwH+731/8sNvt5Ydut5e3B2C/fG9P+jESgGz/"
    "RgxG9r9VAwTUUh0goQDafUz+DYnAnSha5l99Z1l/yQVswAZSGIAugNd/"
    "9xBgCw9E8aECkHUB22QPHIAVDlQdQAMWAibhBgZAasAVHUAI8Cqg96Tm0bj3VBS9jwd7IIBvuN"
    "9ffMHt9vLTbreXy+32QlwAhgMIeuNzKwOqCoB2Aa00KHE+EsIeDuj4H2N+Hf/"
    "TfAC6A4nhgQCQDDwiaKDXiq9KgBEJNPArAtCk0AEd2mpAizW3/lYIoANpBPg3BPA+hjs/"
    "9eXZV+0E8Bm32wsJA9aEoBCAuAABPiEAC/"
    "yDC4gSgRgKRHkAlgsI6v7iEFqJEMgBwb4BGkEfEEDnDlReoAP/SQRgOYIB+IYDMEE/"
    "SQBbXoLNr0jhq4qOZc0PHBSf5oKW519xvz//kbfby8+83V68ABfwniIBgwgQ/"
    "HoRUMv8w5qAoQqgk4DWQiCw+63eD8k/XAPQgK5s/"
    "5a5xzAAqgR6wY9k+ZEMtCOoJABb230hEHMFWQdgAl0Ap/+uc6tKBrrP/"
    "n0AuwfiNwTwNKguHHV5/qX3+/M1B/"
    "Ddb7cXax7g2e324vaQB3hhkMAW92tHoFb96cVAbimwkgQ0Vv7R+"
    "D8iACfuxzKfLvnNlAAjAsBwwP2MwLQAD9sbYJME0AFcg5uBPSAA0x0AobhtcDKDA0j3KYDhk7H"
    "p8uKj9/vzH3C7vfget9uLT9nDgDUZuOYCLBJA8MNKPyGGIftPrL+4gy3eh5p/"
    "lwRUYYAs9Fn7tM/E9lvJwCH2DxJ/"
    "mPTr4nyyLiDtBgTAGCrgNuPzNuETgN+suEEAFhng9lkCoICMLH7V0isCeEMCxylrefkl9/"
    "uzz90J4NNUGLDmAnYXINUBrf5dCCAuQCcCvYVAYPk3G++"
    "VAveVfkIAFRLolgbr2F9ifP33pAqAV/fHRF4HcAS7AKlAAEIYFNwITOszs/"
    "wMsB6II4BXFZ0QwBsSOEYCDwTw2TsBfPrt9uLlqzCgcwFABI0EVCiANl8Uvq0JWNsi2JPZ/"
    "0YKsOiHxftsW4v51ZqAaBWgZf91PsBL/"
    "jFHwEqBR1cCiuJ3gAfCmCEA3cf8rmz8AMZHIoA3JDBPAsuHVgL4jNvt+"
    "UoCH34ggK0asIYBGArsAB7AD+reQgCl+GwZ8LaNlP3MEEDaSg4ACMGr/+ulwV4JsAEfLH42/"
    "vdKgWElAJ4QpBl+LAlKErHwt+oGMgTA2ngE4IUIOH3dGr/hAKT/m/"
    "UBdSJYPuVL7vflU26352sScCWAD+"
    "0EsCcDVxewKjfmAzAsENVn4EfgdySgnYB81yEAgL4RA8T8mTUASAAYBgylQAkL8K/"
    "+zL6rsl8qF6ArAeS7WRGoAB8Sf7isN/VZqTs6jQ5wXlweWfyqpQ8I4I0TmCCAT/3I/"
    "b48u92ef9bt9nwNAdZE4FoOFALYXcAGegkDMByAzzQEgJh+cAIs/"
    "legH0IA5QTCPADE+7ISkD0TgA/8sBIgLQfOgF/"
    "F9kPcr+J8fIYguyCILQRKgV4DNviOzoKqeJS0u4AA3pBAjQSWT//I/"
    "b5OmC0MWB3ASgBrGLA+IryvDNxCgRXo+"
    "wKhjgwk8bcTwUACsJ09ANRVAALwCxmEoFcrAUsuAJ4M1E8BDuHABAHomJ8RgACrZfQLyT9dBWi"
    "2OOEG9NJd/TDQ8HAQuBE97ZhjGKy6o+imnU+4gDckkCeB5cMfud/v6zr9Dz84gOdCAM/"
    "3JwQhF9CAD25gBWWz/"
    "8wNgMpj3K9Lfy0foMMBVffXyT4r+"
    "cceC9bvCcDFP0311QrATPkvWgosYQFLAuoqQEcQuw3v2si25F+M1RkZXLUU+"
    "CgBmCBOEsCbvECOBJbP+Oj9fv+u2+3Zp91uz9cy4Kfebs/"
    "3ROD6iPD2b10YJCXB+0PyrgsHdtBuRACfBeTN+uM+suJPSEDbfh3/oxPoHgwiC3/"
    "06j8Eutj69sAQqj++I0CUfvIpwCEvYCT90O4Pn1XsT5Ve1/"
    "+dcp9FBh3woqXBSEJkvjHHEOUPqJPAjUUCeOMGfCJYPvOj9/t7//"
    "d2e7YmAlcS2B3A8xcPYcBm/"
    "7ULEDIQew+5gS0EIEA31R8Uf6gAoBsgKwBd9ddvBBJAs6XARgLQXQ2o7T8+IETe+"
    "9eRACg7rhCMVgCiE8D4O9wOCb2ubOht1/vYd2ubzLlgKbBHEDSnAMfL6durVm8qBPwXWz7rY/"
    "f7/X/fbsvL2+3Zqv4QAjzfw4COAMAJbEC3wC8koBJ9lAhgxZ+4hi3Oh/f8dU8EqtV/"
    "JhHgWn9cC4CJQZXZp6GAk/"
    "1nawMkrrcqAiwPIIA2FwOB2oaAF5UkcX+GADBs0I5gsNbBQqCorJcFJjqWKvhNMjky0Aek7/"
    "LZH7vf3/vO2215vruAD91uz/"
    "dSYCOAPQzYkoD7vw34sFIQw4LNymNSUKk8Wv0hCYhkoJ74Q6BboO9eDKoWAHXvBiCvAdPZf4nt"
    "3QqA924AbfXV8t8uN4Bt2We029WkoErWpSoCSm11TM8AOYA5uRS4RAITIQDDavaYHxCcm5exfM"
    "7H7vd3v2N9McDt9uxDD//WKsAG/ue32/M1DEACuO3g1jkBsf57fqCL/"
    "7UbIISAio85AAG0VQEYiIC9DJTYfy/"
    "+Dx8HlpeDRK8G90IBHQbgWgD2WT8LoOJ7NyeA5JEkAwwxmuqzur5X6y+"
    "sBEwDMggrqoBNH7c68Puk/"
    "fI9Vwfwvx4e6H724oEA1iSg5AAaAewlweeyLmAnAHQCTfU1CTAH4GyTMt+"
    "QDMRFQFEYQB71lXUAOjHYlvTqh4N2xe5yASoh2PpaJUGDBDrLr9cGIDlY1l+"
    "vDlQOAQHckYMiA68KMFsGtOy65RCGsMIDT+QqJoD3yUwCy/"
    "f+6P3+7koAt50AXrwigM0FrIuEoBrwHMMAUhmQUKAlAwHo7VmAPURo9h/r//ozLv1V7/"
    "5v6wGMV4B3rwYPXEBqIZAQwp4TYDE+LQlqtQfw6my/"
    "LgsyZaeLg7wVgmDnWQ5AA5ZWCDRx7ECzyn3udgFptFCIgTlyFRMEUCKgA+O/jl2Xz/3o/"
    "f7Otz88QvpszQOsLmAPARoBSDVgud02AthdwPZ5BSxUBVr8L3kAVHrvs076KSLQi3/M9QCJ7H/"
    "G/"
    "rf4n8X41XIgcwHecuBMDgAe+BHA6uQgqnvbF5DB5hwUQM3vQgIWkKOVftH+"
    "gAC6cz0RXZ9MjmD5fh/"
    "ZCWCd1CsB7CSwhgArAUgIIC5AQoDOCewJwab+"
    "CH79WR4C0mQAZT4hEQS9DgfEztNkoEECDfi6FAhZflb6Q1XXqwHDEECpvZX4a0qP1l7bfAS98c"
    "QfzQUo9a4mASMC0CsIm6JGK/2i/"
    "QkCuFK9PxmIYPm8nQDu795uy3K7LTvwVyJAB7ARwJoAVLkA7QIkJ9A5AQS95Ad2YmgvAJWwQFc"
    "BpB38pUuB9wVKbAWgCXwV86Mz2ICKTwUWFgOxMEBicr0eoBwCGBUADfxsDsAiA+"
    "zflNay31ZcfnAdAAXgDGkcdAcfZCJYfuCX3O9vf/vtthHAmgcQF7ATwOoAtn9IACsRSDkQ/"
    "wqIIUGoXYEQQ/sL5IDJP539776DwodVAGlr5QBgP8sDdApP3gSUXQa8/"
    "rZsRaBeHmy+HwDyCI1MUNlZzX9iJSBO9igJGJYCo4RdIqMfJQ4Ztq8C7FXjHuSnQ92XH/"
    "yvdwJ4Z68ErOXAlQRW0O9/JRG42v9GBHsuAImAqv+uzDo30C3yAfVHoHeg9xyAp/"
    "7wlp+WFCSWv1sOTBb+0EoAZP5DImBrApAUMFHolQG19c+EAkbpjyUEdQ6gm/"
    "QEsCzZFxKDlWNwprJVWfBm/1WAvWrcQ0ie7Lz80H91v7/"
    "9v263+9sPI2zrAZAEdvXvXMBKBJIIFDcgyUAEvHICg/o7wA/"
    "Bvyt35wCc2F9Cg03RvRyAA34N8hD0xsIfXP7bQgDMFSgyYO8GsF4N/"
    "hQ5ALak1yUGRQDZZJ5VWXgKEsie8yQuH63b8vn/8oEA3lsJYJ2EQgD73xX4z9bs/"
    "74gaHMBQgA7+DsXAJWBBniHCLTtNx2AUnkG/LYNiUCpvX7wp6sIOHF/"
    "lwgkNf8UGagwYMgLMBdgLQCyVgOyciCGCs5nz/"
    "Jr8EXOQOcQZEbrfjjTU8qaCBseMyx4vxPB8iP+RU8A24Kg9R8Qgaj/"
    "av8lDBgcwApQ+QdVgW0bKr3+jsk//"
    "AztzBKgtv4K+Kj08rl7JFgt9BnCAIsQcD2AsQAolQj0CAGAqhOFCK5u3cA+"
    "84dyIJLCPm6buAgoBa5qDoDF6wzUkZ13iSDKKwTamSKZSf29cuzJUwq7LV/"
    "wz18RwH2Nl9dKABLArv6bC5B/+9OBGxmsIIR1AQ3w2gk4RECTfwBulgC0rP96/"
    "FYJUOv9SzkAB/xuKTBY/qsTgZ0LILF/s/"
    "RW9v81ywEwhbeAwUIH6hRwGp+wEOhqoF49fojqQoPlR/+z+/"
    "3t77jd3n3rdru999CzEYAQAYJfXACEAqL8W5lQgA5uoJUK9zxBB3ii9ALiYT2AjvuN72wFILP+"
    "XdlP8gLKFeg6f5QM3AC+VlMMZ9ABGuN+"
    "VePHWL6tHVD23or3tQPo2iWfBRgShDp0ELcBjmIAbwTWqEzIJvLM6kEDEFcD9erxCzg3my4/"
    "9p/"
    "e7299x+323lu32+oAtjwAhgE7Cazqv7mAvRLQcgG7A9B5AAwHus87CWBYsIKFfe+eCSBgt2J+"
    "7QBQ+VsogOU/9fIPBvLhASEF8AHwlhPQ2wVYFhmo/"
    "Wby74QyYLcmQAEbbbue2FcnAb28QTmHQKBwNVCvHv8IESw//h/f7299pyIA7QIE/"
    "LsTeIbqL59hPUADvHIBG8jBIWgn0L4rsKMj2Noomz8QgZELsCoAAnh0Caj8lup7ib9tX+"
    "ZBoKgUmFkWTGJ8S/UHZa/kAHT+QGaeoeQmMUC/CoAzVYAjYDvSNwPCq8fPnINus/"
    "zEfwQE8O7tdt8dwGZjIQQQ9Y9cwAB+RQIC4I4MdvvdLL+O//"
    "E7LgLykn6q3Efjf6X8bOUfkoNYcQZ8z/KzBUBYCqT/YQgjBuOBHxPs7JHh7JoAy/"
    "IzWz+xEtBKBEYg8fIGw+SeQQQ+CzHZP+oWXWPU/8z9y0/+h/f729/5kAN4791X/6/"
    "cpl4SCsDfLRQwHEBLCmJFYH92vssNgBPo7D8qv4CekIHpAjKgx1iffGbKb5UAQwdguIAtz2KsE"
    "Wj7vIQggNON91lYoIFN2mznYKj9UBmwQgXLLcDstRTdBchEFWAWcLP9MgC9cuzM8aXN8lP//"
    "v3+9v/uCUDyAM0FIBFADqAjAsgFiAvYwK3/MfAL8InSd/"
    "Yfy37Qpyv3OSTgxf8C5vZXPfF3aB2AA3hJGg5LghMOgCUBo8SgEAyC3Irvh5xAwhW0cT1iQBKY"
    "Wds/QQLdeVUQcrEjeGoiWH7633sggHfWJOAaAkglYL/wLQyQf3tYsCp9CwmgFIgOgIJ/"
    "JwMdBuB3cQTDX4z9wR2whN+WE9idh67761p/F/8bpb8O/"
    "OotQCsJDhZfji0qT9p0LsCI83X9H8E9KH8iCSiTrQO29bwAAbvlCipPAw4T/"
    "oRKQAVElbaMJ472t7jnqnEjrlt+1t+539/6P4oAxLquawIkF7Bb/"
    "40M9hAAHcD2GVzABmBYKSgxfyMGAbROCipl1w6gs/8ZF0Cy/UIOOr7vHAIu9iHP/"
    "2v77yX9ROUt29+AHVUCnDJgtvSn8wXsnQGzIUAW3F27qFS4z2CrD07wCogqbR8LtGecUwR4vX/"
    "5OX/7FQFsOYC9FCiToBGAEAH83ZwA5AM06BspiPKrNQIt/kcg69iffBegNqVXb/"
    "wdQgIMC0DltUuQ+L+Bmz0OrNTdK/"
    "91+4JVf15SEPMCYRkwEfc3stBxurMS0AoTMKRocaV8cKw6jpcFsdUn2/"
    "8qRT8buGeP55HC8vP+5v3+1v99cADvvfNQBZB4dO24Kv5GAntSUOz/+n1wAis4wAnoMAC/"
    "N9svSUKsBABgmwPAbQTwWzsW/"
    "2vAI6j14h+1CEjnBYZFQWSxj+sEVFyPjgBBrhf+"
    "aOtPY39vRaBVJlQ2vyOGIATQsb6etBguDMSQyAF4IMhUAmZANNNnUNSqBDvtzzif6HSWL/"
    "wbuwN4eycA4gDEBQgRYPzfSGC3/"
    "BYBdOCHxKBHBAJoAbdWfIz1I9XXsf5g9y0yAJB7iUDPCaC6e2EA2ngMGyIHwAgBldncf4ID0ED"
    "XVp1NYmbnrclOtyfDhiPOoCO4CEXB/rOBfOZ4yy/"
    "8a7sDAALY1gKAfWMEgOovoNdk0IArKr+7gwH02gWQ2L4t/sEEoLL2IQnoFX96HYC4CIz/"
    "jcSgAJSVAtu2RPZ/"
    "SPRBHkC7AkYEqceC2fqBfdKaCcHAAeAkpKVBCANcElBVgBQRTC4HngHOTJ+rQo2jhEbP6xf/"
    "VU4AmBza7L+EAZgLgGSgxP8dGQDwmQOQbS2xp6oEWAnQn1seIEMCJO4fsv8Q2w/"
    "JQU0IJMvPiCCT/NPuQP/noJ0rAFBa23VSr1N/"
    "vQhIgxzzB9odMMIAkGvFZPF6JkyIlJeFFl6IcRYYX0ciOOOcll/6l+/3t/"
    "7fngPYy4BSCmyT0SGAlgvY4/+BAET10fZjUhAWCg2AV8nBEPQ6D6DJgSUAoQ/G+Dr+T9l/"
    "pfg0HxAs/e3WBUhbsihIgHKkHGiGCQHYO/UHomDgdd0BcRkZlYtyAFlgZNtlzqkSJcwc1xr/"
    "6FjLL/tLPQG8t+YA3tuXBKPiqISgAB//bjZdkoNE/"
    "Rs5EAIYXIAKCwYHYJADlvhalp8RgS4PogNwFN8jgo1A2LoALxRw1gA09TbCAjckQHBZlQEFwEo"
    "S0Iv1S3mAYFGPlwOIJn+0v+"
    "ocPohEsHzRX9gJYM0BvPvwTyoB2gGsP6iEAowANsBJWAAVgRYeAPCb/"
    "WdkAKEAttNJwRbzM+UPQI8K36k9Kf3RagBTe2vhj3o8uAFXLxUGxTdXBrK1AIltTZ2JzUe7Lp/"
    "Ralvxvrb5kcWP9nv2fwBzIRF4FRFkx/"
    "XcwRljHCGm5Vf++fv9re+63d4xCABVRhOAJoOtRCguQKoCmghwv7L/mBPQwB/"
    "KfMQhCEF0ym8RAUkIToUAxrP/"
    "gxOwSoDGmn9WCjTzASw3kHQA5poA7Q4g3n+MEMAChiadiopXwHZV26usvB43e/7Lr/"
    "pznADakmBdDcB8AFj+5ggcF4AhgAlwwyUM6m+pPgF8U3BS6jOdAAkJ3HUAO5C7ZKBT99/"
    "IVDsGhwyY3e8qNfhCERXDa5BrlW/"
    "ftaoqe265Ar0U+PIQQCUzqwqYBYfnSK4AcuW8sjmHaMzl1/zZnQDeud3eXRcCrfH/"
    "ngNYbyxzAKL8nQNAMiC5gI0gBNz42XIBAnAkBACwqDyWByPlp2BPWP7WD0Crs/"
    "5ewq+1JaBnWX8rEajbDiVAlbNpwHRyAJ4D6EqECQcQWfxo/"
    "0wI4E3wcPJnUbSLXqH5A26qHaD9kb7ssKaj+nV/ZiSALRG4rwhsJLBfUKt/"
    "k3yAJMGwEtCFBGD/PTIY4n6d8ANyaEk/Q/"
    "nPUv8h+"
    "WeRgXYCVgIwSwbK3osKi4PonEGUC2C2Pngc2LL73Xanlj9bBTg7BIgAFe2vuoxZS14B7wy/"
    "DCT8xX/qfn/rrYccwLtrElA7AJkgkrDSJUHJfO/Z/"
    "wZ4Kx8g4IXyYKfm0i9QfkoSJK5HghALr51Ce2Jwv0ad9BvAj1WCidKfZf1x3UDnvPQ90HYf7o1"
    "WfSQMGbOpU1D3H6oCynpjPE7VfSccpoalMEHNdAxFKkDLgDzTRo5ZaXukz1E34f1Gy2/"
    "8kzEB6MUlsjCoCwWMEAAdgOcGTECrnECn+"
    "JYTgPyABn0U82vwt7hfJft0rK9DAlHooTSolH94GxBUAnTSL/"
    "reAbz6UBADt344SDkIJBIT5E62HgnEAwgFmjq3ChFkAJUFd7Zd9fwsdZ89nnX85Tf/"
    "8Z0A1hwAOgDJAxBbuU1usboYCoiCKvWX+L/lAUDlNUG0bD8Bt7dviP9Vf0v9LbV3XQCz/"
    "3qbZf2d0h8D+JAPYDb/RAfArL1l92W7Z/"
    "OjEICpOZvkw7bES0EisET7M0RxRNkzx78qJGj37rf+MUUA+"
    "zoAnQjs1gTAhJNyFy4X7kBtkYHKB0ifDMgrLiADfJMESGa/Cwe0/"
    "a+"
    "CHsmA5QQ8N6ByAzJZh1IhEobOAegsvwaVDhEKDkCre0cielYbau4SQfIZggyIM0DMtMkc6ywnM"
    "HMsduzlt/+R+/"
    "2tt2+"
    "3d8QBiAtQSUBaEVDxPyYB22cEuiYDQgJtLUFk7539ke1vgAeAR05gC3ekbAclwuaEjEVA3XoAA"
    "nLpT6sBCuStrUrIpqsBHhkwcBOVTecFJAteCAFSyk/GzapwBOJofwV0mbEQkNX2p/"
    "X9HX9IEcB7eyLw3q8IlPgSbV/"
    "LBThEIMreQJkhAeYOIsDrsELV8VmIgHX9ITGo1L+BnxGB5wQY6IvKLzZZCKD7nsj8m+"
    "sADjoAVHk9ga19tF1CzSk5GO8T9MCUAdpZbSqEUW17lpNYfucfvN/"
    "fBgfwLlQBcEnwdkA9cdGiCjCgGrCpZhACDMSA6wL28dewgKl6GzuI963EXwtf1Nr/"
    "wQ0YMb+"
    "bCJwAPgKc5gPIPeiImeUC4B5J2zbZnGXBQjI4Mdk2HFNPYqv9MNlJCJByAzPPEezIiUAe7a8AN"
    "jPWGYpePc52Db/799/vb7/"
    "zKgQQAnhvDwH0cwFWLqBluwkRYJ7AqgoMTiHjApTqR9ZfbLxbCbCUX1wOKQGiO8ASn7XdKgMim"
    "L2SoG4nkxGVnqk+"
    "OoeBDHR4AN87EmCWnlULBGiBuiNJMFC5RJB8HsACRgYwZ7WpEEY2pNEuYOoYv/"
    "f37Q7g3dvtnT3+39YC6BBAv3IK1wVA9p8SAYC5gRDBqz53QDasvag/dQboGMCy0zBA7e/"
    "CgoTyszX/"
    "VeA35QeH1YGc2Hwr2YchGn5mJNGVd8FdoEOIHEBo9VkeQc3cqFJgEkPhxSBHwoIMCVTAlx1vlg"
    "gq4y+/7/"
    "fe72+"
    "tDuDdV2XARgD7isDtd95BpZWjKRUov4Acwa6BT5OEsEjICg1aBUAl8DpwA2kgQeCYbHsjL0zyg"
    "fKbll9XC5xk3zYGgM1yA0IKERGgI2PJQJ20M13CAQfgWv1kEjBj+"
    "Yc2zlqAGdWPgBPtrwI2O16FXMrn8Ad+"
    "z04AaxVgTwDiasAtBNgnrK4E6HBgSApichCBBHkBCnQNbmb1iTPoSEXlDXCfTv6x0EAA2OUDtC"
    "PA70bMT6sAXjVAlf4sIhieC8BYXy0CYk5gIPKCA8CJGzoAI5QYJqoRzx8NAZ6KCLLgzra7igSW"
    "P/i79hzA6gCAAMQFrBMNSUCrFypUm+x78k/"
    "cQRffY45AqatOGDJy0CDHkh5dDERielFhWvrTIYHO+icy/"
    "jK+qe6sCkCAH70erLsXylXMWv5GFowQrLyACISU6HZ0W+RALX0Qz2ug4NgYUWScRNQ+"
    "q6IZ8GbaVMCdHS99jX/"
    "4dwIBCAmsoNd5AHAB1sRDArByAV1YgLkBnfRDF6AtPbP4LNY32lkOgMX/"
    "tPynSKFzC466Y2JP+mT+mk8BOiVAVP2MA9COgH4nQGcgHxyCAe5uMicqARTcJ+QBIlB5+6O+"
    "V4E7c9wMCSx/9HfkCEDyAMPDJiQZ2AABqtZUVwG7s+ZWMlCDO/F9iPFZso9l/"
    "IkDaMRgxPqe4g8JQa30yg14pdaM7TddgWHxXcUPVgLqvnqyWw6AqrlT0jPV33AekYJb4IlAdfX"
    "+6LwR0BVi8Yhg+WO//X5/"
    "e68AyLMAawlwCAEwF2BkpTfgqwlu5QU6G45KrdYNsNi9qwAQMgjBnyEDI77XYGcxfjXut1wAhl"
    "fSptsGoNHJPab6XkLwTAeAk1MIidp+mJlRJYCqPxCABwizr0aUDl3I/"
    "ogEMsDMjJEZp0oYjECWP/"
    "HbSA4ACEDWAbA8gJ6MjADWbYP6i5LqvyRROBBABHgjXEAV14k963s7d0koOkm/"
    "s+J+FiaERADqbjkAHKNNrsRCoE7lmYsQ0HjlPm+dgMzKRLmQkkgyBJhR/"
    "SPWPwPyTJuriWD5U78FHMB7eyJQ5QDaYiBhXL0mgGWumRNQAO/KbieTASMOL8bvVgUSq2/"
    "lAvAaOvDiwiEjs6/"
    "BThdZ6bUBJNvfuQN0Z+pzVzI09nXqrT3UMRMAACAASURBVJcKg+"
    "J6xKAnLao7Tvruc6ZcyBS6EDpUXUIEvgyAz2oTnQuqe+aYzT386d98v69rALZ1AEIAazVgz/"
    "4zBzC8aorlAdS2rkIgC4e8v2TxkOsGMLeA45I6vgZ7ygFg4g8JQhOdl+FPZv+"
    "ZnRey0CQhE4PtH1TfCBmkXQd+S+1ZXkCTiQZq0gG4sb6qMHSAKFYQHpsIMoDMtKla/syYy5/"
    "9Tb0DWGP/7R8QgOUA2NtnzEw3LhRS6hjlA9CK6/gfS4XU5rOk427p9bg02cfATtS9CwGcSsB6/"
    "taTf9Zvx0ItvQ2JgH7WgEYyMMA+5AwmHMBMDsAjAhrPTz5M9H4mggy4M65g+XO/"
    "YSeAXf1lLYAsBca/"
    "24D7MwKdakBIYOUBxKYyJ0BDAeIOTOW2QI75AgVkXNVH7b+VBFTgDisAQda/gd5LrCrlZpa/"
    "WXJrEVBk+cGxNWAkqwDMQWiFNq2/zNKgDOi6A2NFICULRAV8rrSN7HgEzmh/"
    "NH4G2MZlDi8qXf78Fz8QgNj/"
    "thjIcADtvw9HNcgQwGxIwPIGLHTQVj8BfszWmzkAlZsQwFrlPbcCYOUCjBwKKwl6pUBRWyFhuk"
    "xY7LmO7414X8f61BVY4YLY9iDBhy6BTX6LPJCoPHtcAXelbQRUD+gZEojGZyCvjrv8hV/"
    "fOwArBGBLgnFpcGdJYUJ0gNknxLDNCwm8xKEV6xtqPwt4DWpm92kIQICN7bSNF2Xv/"
    "pLfUgNd5wxoCEAA34GbqL0VAmhSuMIBuIqv8wGJRUQWmCzAfNIQwV/"
    "8tff7O+9BEhBKgEMiUIUAXjLQinMbAAAcCIruFWMVgBPFX28iLhW2Yvzu+"
    "JCo06A21wAQm69XRVJwk+RpaiEQCxeQKEDlaWhgtEWQWEqvt7vhwoQDKAFfjR+"
    "5hytdgjf20X1HLH/kIpa//"
    "GtUCLATgE4CogOQz628IwzslKx0gosuG1bWnuUGotJhyzUYYUIjBSsnoJKVXZnPCAeYo3EBH1U"
    "DDIA38CniiBR/CA1I1r5VEQBUg/1XVt8jjG7iWZUD5WEz5UIK8sRagIhYquQQgfqI/a/"
    "aeBYKZMOD5a/86r0MCGsApAqQcQDbgTQBMNuqJ70GE/"
    "nuOgMSGjDFj7ZZhNABnxBTIxon459Vfa9yYpUEEfRU5RXounEUkJEgGJlEYNb9O2IQ16hsO07y"
    "9nk2ETjzJKG4JIKUSlgQKqyDzgzQM22ic/"
    "AcxPLXflXSAew30no8eDsJvBGWyhmJsKojQOAOi3R0yRFtPcvuqxo/tf7qeryYv2T/"
    "mZqT0IARgfzmG9Eg6erP8Jvr+4Tk4Sk6IwnWfgA/"
    "IxsCPhmfKWuk3ugcqENIgLwC+hl1j4Ac7c+CPDNOd4/++q/ccwCRA1iFHkqAtBrA3ICh/"
    "J46Yp7AjM+DHIK27t1aA0YIbKGPIisrw59NAOqSH/"
    "0NEKyMCBS4qwnAtNpnk4JGnN8pfKYKoIgiA2R2DEYglW1XE8FZQI6AHu1vv8nf+"
    "BUPBNDKgFYOgDkAsHdmQhAnkhP74kNDg72OwgMP0CRuN90GW+"
    "CTdCwWoVluQKv3EAYQ1cZjuOpv9JXJNyT49KIgliMwlByVu7kJUFwvPBjcQuaxYSuUOBAGZMjG"
    "IxEP1BEQn3z/3/"
    "oi4gA0CQD4uxAACMBLCKLNjFSPJd3Q7rtJOWu1oZNcHMgmE+8H5T3P3Xj7OlCzCgEeN+"
    "sEVDs8Rpu4Ol9ggd1ScuYWkAQIsDv1lrYqB+BZ/2FfsBqQAe3sbZG6Xwn2aGzr3Ja//"
    "cuJA8CnAXfr314SajgBkwBwAs6EAwmwWWFChThY0s8iI297B3DDPYRtCLi3Psb2AdRAHrKvqb9"
    "BCEyNtaKXS4OkoqAnomXjKUEo9e/GSjqAs0HvAS8C5WzfaNwKES1/"
    "95cZDmAlAbIacPudIRcgi4H0oqBuUirgU6WDSVtJsHnJw8gtZNyGWeJLEJNn61vZzYjzo/"
    "3dQ0Ea1DgmUXMWAqTAbil9UOaLynttQj+iAzibCCLQRfstUM+ShJiqqP/"
    "y937p7gDuex5gBz5bByD23woDMA9ACeCAG8jkCLTis+8ZUhjCAisZOKvwySw/"
    "OoWONFWMrmv4ZsWAqX+wrXMGbLkwnMvgIowEIWuHTsV1CTKz978WeViA88IKDzRnA/"
    "Ts8TyCcUng7/"
    "+SngC2twFZJLBPljIB4IQ1wgA9waPM+"
    "rCfJApN9Tae1beOGZ1LO06CEKj7UbF9A7CVB7AShIa9R3Uf1gOwhF9V6S1iEEQFDqFN3my14IJ"
    "EYNYRTANNERd+PZMMIsXXp7H8g198v68VgHf2uP9dBX5xAtvbgaUUqEqCg/"
    "1HKweAlx9vsLeGIlqxchWojCyqY1RCgXK5jxGHofIsD9B+"
    "V92nSAgIxCEkgLEGBU8mAaO4PgoVmEJbOQQG1CzIs+08Msg6kAwRzJBOlgiWf/"
    "SLRgewksCq8l0YAKBveQAgBGb/"
    "t4vDhJQmAwf4a9dQeZPWnJbiHMfgOYeNlAKlx3BFOxs3L6B+"
    "LySS8EUg6rzwuEgQ3luBGugDqx/lCzyCGPbtCBBi05M9Io2OFB4hEXgmGLMgzZDEjIvYruUf/"
    "0I7BGgkAJWAbY46SUArGThMyAIZVADH2ppEkiCBir2n5xmpu5ME1I5pUH+"
    "LYEnFICKEDpiFEADPSSu0JhQX/MphTBFBIYnI3MRjgLviLs48H9OR/"
    "JNf4IcAK9bxPwoV9TerAXgj4T0BOJk9MhAQDZOfACUCNgIy0zbTJpPZpyGAQwTiKug7AYkr0L+"
    "N991Vf00gpGyHINbK3yZVMQQwVT2xEMh1BEZ/Nvk1EKsKmgXyGeOeTQQdEf/TL3wggNX2b/H//"
    "jqwLRGo1gC0HMCeD9AlQPw+"
    "WDqZJEZIoCdaNY6OgOmFAVq5u7ae3Y9AHam7sd8kApUsZHaekclAvrv86eoBcwkZkFvrA1hf1w"
    "U4Cu4Btu1T/c8G/hWgrxDEmSFDc0D//"
    "OdDCEAqADoPIMnA7a8wrv6LpSEFfJlkoQtAdfKShEmAWlUDN7xgOYYE6DPuBY+Lv0W0HRXdK/"
    "cN2X6l0jqcsICubbx2AVeFAK7Sy+zV1YDiasAjgH6MvqZth+vXH6sksfyLn/"
    "eKAFaw6yoA5gEE9FYScDsZZfsR8CwhSJNb2Tq5UVLsQO0lE5Pk4bqRiBDU/"
    "oEcHFVn9X1T4dFZ6TKhYfWZcltqbm6HsZm6D07QKuGRcqQGgEUKSF5N2QySYPutbZkw4SmJwCI"
    "IJIXIYSz/8uf2BEDXAWAosN/w7gUhAHwhge7GY2wGBKFtf5oMGKgcl1Cx/"
    "wKwKKQY2hWB3oHbqver7ab6J8t/"
    "2L9VbaR6sM8auk4gArlRNbBchQnSaBw5RyV7lRCAgSYCerS/otRZwqiMmSECc7x/"
    "9XNUDkCvAyB5AAwDtrlBQgG8KegCOsvolQgrgPKcQKTQSReBhOCquBP3a8LTToXF/"
    "vpY8ls2J6AdBFH/rNJfov4YDoL6UzVP5gDc8MBJBFbBnwHrWW08EEcqrvhw+5oNBZZ//"
    "bMLBCDqb7kAcAJtUQeyOuQDcGIPnzFeJQClSbJqngBULW3xIzKpkBYe3wGxkISn/"
    "u5zASwccLbh5NHhht43ELsFcGeFXwfmA1UAdBsZ9YxU/"
    "ej+zDkwJ+RtO5Mkmhh9yc+637cKwJ79lxyAlP/"
    "kKcC1IqBzAJgL0K4AQwC0m7hgyAsBrAVEaL0HJU6SQKeiyT6dWictOwsTsqW+9ttosAax/"
    "pA3AKJBEqEhQLX+T+J2PG9GEIxEPPC6ag/SNzhOtm/fZo3JABYpfLT/"
    "KBFU+leUvxHNR37mSAAC/lYBUDkA76EgIYWOAHASKnXHm4/hwaB8pIxIV8oFFpxlziNws/"
    "0diSgF91bwuQQmE7QQ+2fUvwO+pf7KkXRA9db6W6QB1+KCHu1qMgTQE70DoTOG24/"
    "Y5qMuIEMOFYBXQ4FM++WjP2MnAFUClGTg5gCEAMhy4M4F7JNou/"
    "eZ0qBWELD7qO6D0uNkZXmEwKqb4HXI4wzAa8ejLTYSjb5mfXz8jgCvlP86YrhC/"
    "ZH4lfpSFU4SgAfMo88TZFxAlRgyY1aI4Iy2zQF87KfbBLCVAAP199YCaBJAV9AlnAxX0NqwnIB"
    "SrHSSziAPa/VeJt/"
    "ACMp0AY6l1+"
    "CNvofqb6h6NikoJMMUHN2apayZNt3YxRwAPa6Tb2iTXj4cVP2MwkdkUQFz5njsGt1tX/"
    "rTHghArwHY7P++DBhdwDanYCWgzgPIfh2TtfUB+"
    "6QcJhcBedfGUXoGwAaOyXhdKy4rC1rxPAtlymqfjP0x5h6ArVSdARJdiQa6BWC8t3h8RhQ616A"
    "nY+cEigRQdREWUZ1NDBnFz4I5Y+OroMf2y5f9VE4ACH50AS4B7OD28gDtxyEVgW6yOIQwWGlg/"
    "Uz8bQLXcBoa/AM56Dq8FcMbCTyx/"
    "o3ISF3fsvaMWPRv7JLEPht08nC4TyTDb5UNI1VnwO3coaHQFPBKxa0QwAO/"
    "G1LAucwA+2oHkDkny2Vs27/"
    "8pygCANUXF9D+"
    "h2CdC1CA334rcQf7Z7yxsp8qiFpBOKhPQAiW6jIlN9UdzllAKQBjdtxT9eF8HJLQ5xNae6Lska"
    "1nSu+pfyMjb3GOlxwEYrHANwA6sO/abdBxyRiPAf4ZoGf6WOA9y0Es/+YnAwHs4JfsP4v/"
    "JSEoTgD/"
    "is1veYFZEsB+"
    "xAp7gDEX0yRU2asQaHX2wD8QjEEsCDKt0pZqM2LpSqaiiNpteCW7mQSgukc4UTWxsH0Z8EaKT/"
    "erRGIW/E/pAo6AOdt35+Pxvwf/"
    "t0gA8BKQFfzZMiDmAYakoJ4oUB2gE4UtHDLiYQSa9bnsDEhJj4HfdBYHF/"
    "V4Vn8gvh3sh9Rfk60ot7c9Uf+Xc80AkDnCNGng+RrnzCa/"
    "RS6Z8zXBJDv0ORnf9bHY96Pbov7LV/ykMQfQrQMgVQABvP67//60BKgXA7UTU9Z/"
    "mDgk+TeAndjrBtpCBcEF9Wz23on7j1p9TW74mzaH4jgC/"
    "Vtri20uDdakzvIDbTL0y1I9Gx+V8CJHgNeTBfIMEXhjz5LDU5HB8pU/"
    "ccwByBOAXQ6AxP9sQVBL5EJGF8uByPYDCehJE1UGAuB7JKD3MadA22iFx9DCiPPpeZAFOZWyH4"
    "6Jk2cDPiZFRX1IvI7XrMdg2fsOvCRsYGMM25QadgC8KAeQIg5BblAajOL26v5Z4DPrb6m95wKW"
    "f/cTxhwAPgJskQAu/"
    "aUhAIB5+"
    "22J9aelQa0uOuFFQoRBCY2Soc4PNBDBMQVAGJ50amqVI8kYOH4F3FTZsyU9EvuLMs4q/"
    "NBP3SNT1Y2FPQyQcs0RYYT7JxYTZQgiAmoE/Ki/8E80DgO+RQYe8Nvx/"
    "v2P3wng9updALgAyEoEYrY/ejS4katyBegG2OfOEqpSX7s4K0QohgVUpSft+5VgR7BFsb/"
    "nEkxScByD/"
    "s31pB2IIOMSIETRE9YLF0wiOGMtwcUu4EoyyIAe79uyEsDwIhAsBSrrT6sAuyJ0i4KU6p9CAkp"
    "l9boBNuHT7iCw9vThJBJfe8erKrt2IZZjoWSIcTkLCTwVt6oC6nojwLKYvuoWIsUf1DsZRljn7"
    "m3PAPcMBY/GqIK8YU/IHTYs/"
    "+HHKQLYAd+tBCQkMIQA7L0AQAxo8bbjI1MXPiOIqMJNOgIEly4HmvsUIaUA7oQ0tD/"
    "LuBsAzTqC7XosUnAy/MwBZADtKTl1fjhB2aT19j9RCHAGOWTGyII/Gyos//"
    "HHAgEo5c8kAbv4X6m+lRDEmy73EtViSEA5pcFOIVTSMHIEAgTLVuvVceXVeFWwO3F+"
    "ByIW5zuxv1ZRRqL6d2TK64E1Y/9dIiDWfVB3veqPEcEThAARcDNgPKtNdC6Dw/"
    "lPP+Z+fxcWAOHbgM2FQKDsQ/"
    "wP+7TSo+qzsiAqk1apLmGoVUor4kTpcCCDALzZen1EQpbNp+"
    "QEjgNdiZWxN8t4pCKQUXeLOChZOFacEoFxTmzsYRIjEZwQAnjjRwCL7Hu0PxofLnVc1IM7gzxG"
    "E96vWgkAHwUWF8AWAuGDQOyhIAQ/"
    "KwPu+"
    "9t5KmVvJwXtMHSgE9BQfU0g7oMy2g4byb9ZMFtkwUCMhNDtJ2VDDVoNLBoSEBLpQBYB18kPpEl"
    "kv9HM1XRzwFB85gzw2BaArX4uoRRAFYG7up+RQYYgKm5i+aof/"
    "RACiPK39wAAEbB3ArSq3v4Bl//"
    "qpcAa8Nt3QhAM7N0FE7DTSWc4goEUAAwm8Ky1CNYCG69syWr/BJBWLkArvWflL1H/"
    "iDwE2I6dH0hKJkeyYtCRFYCThSdZYLuEwo6hCGwGlE9FBsNx//"
    "OP2gkAwwBJBBoVgK4SsE8KyQWwuJ8RAoIdCQJvpMXqVnlQA3z4TpRdjsHA1IEo6hss7JFzQQDQ"
    "YwaE0AHAUmMrSWgAmJKomuRH7D8DmOVWGMAjgHb7T8oBeORR2XcFOcyMyfps2776C/"
    "ocwPr7df8rkEMC23xS/"
    "0uQLgVm3IBOAHYni1ldneHVcSMJKdbJEYYOQU7BDR+"
    "M8VMZeQZUY1tHVNYxlQJnQgJNKNbk9tzGAFovx0CWDXurDkPF1+"
    "MVcgBZhzDbbgaoVWdQsftNaIHcNwLQIYCQgCh9SwaC2jfgQ/"
    "lPg92qAnQnokIB6gCUcrlVAqNsZqqco+xMtTM2/"
    "FTwVxyBofAsvGGgNe25UxqskgxV+ETIkCaCAgFEzkLmqdXuqZ1ARBam6gMAl6/5kSoEUPYfwa/"
    "fBNSeBQBi2MZW7wRox8skBgnYTUfgKLeA11O4KDk3gJ0pWzI00BOYxuhOeU9fhwXWqdg/"
    "Io7MfuJKKNhBfRrAJisAFJgH1wF4oPYAF4HxyP6oLwN6xhls/"
    "f7Lj7jf5dHf9hdeBNoRgJH5L4UB+2TSpBDmBADsCG5U9izYq+"
    "Sg25uKqqsJhnJ64JdrcC13Mfan14tAdDL76MhM0qmOFdh2fRxGJBZQoycKI7BkQZ5tFx0v2h+"
    "BPw30BrhXH7bweCOA/eWf+kUgFvjxKcChGqAAbuYADCLQ4N5O14j9I/"
    "DjftcGe1UDpn7Ogh2LhCrHfyzw098Hwews/"
    "aVkkMzkD8qd7JciggNJQItUjoC0CuAjxMLOMzz3r/3h4ADgLcDM+ktOwKwC4HJg9ZmV/"
    "RoXWaGBUv1TiYABO8ofWLHwRDLPBd8JCn8quLMWPeMkiPozK5/"
    "dNpBCkAPIgnwWiLP9QqAqBc8of6rN1/"
    "3wh4VA8gRg9AxARwI7iFgJUCcAKwlBFg50lQIdDoCbMC1rpYKQrBygW+kUMcjkR+CsxvHus/"
    "sReCPQRvsR0A74rPCBnXtK6ZVTsdzgYwK+ovaVthE5zCi/"
    "8MnydZ+vQgC1AIiFARveINHnJQMbNlHlAbDbiTj7NBmUiYCoNqsiDBNUT+"
    "YjoHaSh3Lz3BDBcivedkaSjvqa8X2ypBe+"
    "QEQBVl9vBHrmCCi4H7EKcJban00GFcJYvv6H9UlA+i4AXAuAZT/1WWf/"
    "LdXv8G6VAQkxlMHPMsJFJ3CJylugstTaU2FPdT3wZpQ9UZ4LiYvU/"
    "TswJ1xDRsWZ88v0a0oIFjtDNt7YEQCPEEc0dnX/"
    "AwGQ2P9oDkDCAvld9XdP9dEV4I3tbpaenMZ3V2lIn0yCSlv0wyTh1Nkz9p6ppxVGoFU2VV/"
    "UOqn+6NKiMbtzdQgmcgRv1P/hJlXdw/C7/"
    "dcfajsAifeFDESU27MB+wa5jzoUaOB3LD4SA4v9NVF4LgAnd3ehgeozAHugHianEx6wCR+"
    "FG2YeA294whVQYtjvWQRUMw9BlDIkG7b6j4VmVrusOp9s/"
    "y0ncJX6R+POAD4kiI0A4L8BQ+Uf3gfg2H/"
    "2MBBTfdP+C7vAzdaPAFfIwLSERHVoIoqUBjNKm3EDGVIwx8kAOFLuaL86hkkkxcU/"
    "jDgrSh8CUhG9B6iMzc+0iUB7xO6H4EWszLqBb/"
    "ghJARgTwKytwI7OYAhBHBcQDYckOtlTmFYABIA3XILbCEJ3QaE1ampsRItHTbsF+"
    "mqqpUryCzZzYA/QzJJN+ICPLFqLwPCI/F/aXy5N4YjiRT6akB7BGmd2/INP/"
    "ghBGjJPwL+"
    "1QnIfGf2X8CuQ4GGEZXoO9UFEOdwhAxYDiCtXE79ngKh2t7LFWTAHwAbSTEKEby2kaqznEHUJ6"
    "XmCUJJjaPUdFbFK4CvtI2IprJ/"
    "+caVAHQSkD0ObL0MxCgJbnNNqb7+XlX+KATYLlwdky4NZVaRxY/"
    "ZcMGLZwNHkCaXCPwZ1bbOBZXNyS0wkJruSKmll1w9CsrHdACzZOBdYwWwYj7CcAhcijf+8o0/"
    "KHYAkgzs/u4Trqm+/g7gKYUDRNG7F4jKhTlAbz+SbgNjdz+g0S5yA0wFO5AQAnHVzwOoZ/"
    "vPAn8yMeclKSMlPwOspm1nhO2oeRZEM+0qgH8q9d/"
    "O8ZtWAig4AMGQuRDIWQ48JAUBkO3eRcDWuQSi+pETQOBSdpxQ/"
    "kjJI7IYljkrVXaBlajpZxbqeGrOQEDzGqA8OoywfvdqHP5+"
    "IICznEKFSDJOYhjvm35g0QEkFwIh2Bm4w3AgcAJ6MrV5R+y9BpcmCFQl+oOz8MByE0qNu/"
    "EK4UDkJBihWHF7Bvz4m5jAJct+I8Wn+6+I1a8YE0k4+OwBtaLwlbYZwIfjrQQwrP4jK/"
    "82+6+2y8q/IQmolR2SiNvvqFUc3x/"
    "A9jOwESfAgB6BnxGJFR6E9tWbhJ499ey9FUbIhDT6ejadAjwKMbSVtkgxY7kvAOuZjwFn1fvq0"
    "CACeAhucGPycejzzT9gdABYERheCLqDUQhh+0qeC2iYNcBvWf4wMWgQhE7+"
    "CdHoC04TAlFy0zkY6+41udAJkyANar8JKVIHEBFEspYfOZLIxofkmSEOr82B+"
    "H9WvWcIoALaStuILNj+bdtKAF4JUKu+uQpQx/"
    "5AFKj6NBwQeiLOYCCxKEegCELb++GHcCoCA2taYHXU0IrtXTJhjsd5kKcDpziDBEEgQZkkg+"
    "MBWVigiYjA/T3gZofjGI4kC+azwTszXgTaqwlgHX/"
    "5ls97tRRYVL2tADRCgUH1yYKgDofE4nc4VqDG/EGbE0ZiziMIF/"
    "yGYlCHYJEKKzviJLaOEWTbQ5CQpN9AAhcoP5JWGaBA8lmyKYHZI+"
    "FgldwMeLNhgncNlX0RWczufyAAWQqcjP2tCgACV+Z+"
    "t0RYAUmIpAOxEdtHTmDbTybBsHaAnIMmiuHmatcBk9m8iexcEgrqVgP2c6cxvFL+"
    "LMii2HkYJ5Er8H6TaeL4ANj/"
    "CKSPofiIowcH8P23COBGnwHQhOBVALxHg1l4kCED0mbIEVjqTIhk+"
    "4GT26dJIXAF0yGBQR4U6MR5ZNsNTkIRS0mVsa8ir+o4LnF4ZKvPYXKV3xWK/1o4gG/9/"
    "ioJKC8E9dyAAXaM75sDANDp+"
    "N8LA7p3CyjF1Y5B3xxKEsZ6AVo5SIDYZHMvGRUlqqLseLCSbzunpBVGMsy6hTA0icAWXf9sIjC"
    "45irZyPzKuJUjIH4KxR8cwLd+v50A1PMAmOzTnwXTYvkld7Bth5uM+"
    "9uBo3yAodKR8uP4HUEQ5dFtGYEM25QCDwQQqVAEzAgcQdx/JvipC4jICX50Cpxk/"
    "wzoorCkAsrM8WbHM0WCEGXU9qr9y0oAWwiglH8LCYz1/"
    "w3wqvznqr5BDhqsUwuEqg5BkUwHdgOI2yGsx02tHIHcaGd/"
    "pMQIbArMRF7hCGAwFMqAxWwTEdys+"
    "sO9zJzfjBuoKPVVba8lgGISsFsApElivyE45wdXADdNhwUdlkm8nnYCCeWXY+"
    "l439tecgvG5OxuZqSMjnPoJnwWYJETYUoenWOkaBP9M2C2yDML8my72fg/"
    "Am2FLKKxZvZvfb7t+"
    "77KAWxOwEj8NXUHp7DNb3QBCvwSAnSCq0MAQhiitugOcCzcbsX71qrAri9OXEY21nMGHUu9GnG"
    "4oQVncMg2Z8FPSDEFNMcVHemf6ssIidw3a6wsyM9oVwXhUQLwznkQMVIKbQRAV/"
    "45RKDJoAHcIQMhiwjUQwjQscer3hYh0BWBxhhCNCzej/"
    "ZZx9FuIsolHLbMFUWfAXIUviAY2ecKOUVjMTIoXH8EmAwhRSA/Cuoj/"
    "c255pHot33uQw6A5QFku5cLQGAjMSDmLCcw4BImixUaCDCZkntuwGtPCcABCx6nHBJkVDg7qSu"
    "vwEoAcQDIBPi9MTIAKyt59rcKyGWWHCr9IvJ4kv2NAII8gIC1Wwqs1wUAoi0yEABrx82UP+"
    "sGziCFDsgkHLDyBN1N80gjqCLg+CkQJOPqdn4BUOhEniENVJtE/2x8TduRa/"
    "IAmT1WBMSzxomO8yj7P/65r1YCotIPn0m8j28BFpVvwGdkoCRf2/"
    "gOd1k3MNgImIEEyBZZYEKJugVrHYEoi3EsTSzu5HEIZCCFyuQPnMIl4If7kgVMtt0hUkOCMj5X"
    "gVex7VM2XU3IlEAQxyPDdP0//"
    "n3GlYAh+FWs370OXBbbqWSfblNxAlbbsuUPyMLLBeA9YLafTZruB8+AO2vps+"
    "32650Flqem4b4T1d881oyreWICqJLL1e2XjQDkjUDkmX+d5WffEVeWE0CBNJU/"
    "qfq6f0eQBdVv/"
    "Qw1tdyCBWzGsDJGqBIZgiCAzjqK0kQ6A1hnjOGBNUEwIUmd5AAqxyndB0PFw7nkOAY9R5ePf+"
    "9XSUBGBAJudAVt234Ttn37xi4ESGyTE0rnAIBtBqwfAD/"
    "+Zl68r8nGdA3RykEsy2TtfJYkKsfWk+wM4GavJwnA2fj/"
    "CDCPgqzSPwoLov1HSOUVAeBKwGgtgJH80+AfbL8OC9A66Od0gFy0UiuCa+"
    "Sjt0cKboYQRGmHsR0w4vmGE0GRltk+AapuIlTbG9dcDh8mxpkCauL6wt/"
    "eUcojfY8AUiv0Wd+tc3ogAA/8xsKfDuykTVP2/YO1GlCLNnUCiii0Cpu7LUfgjUf2WTG/"
    "JgXLORwFtbkE2VLQRNKPTgiHjNKASBw7PZZ2J0Vnc+Q4ugsk6gAAG0BJREFUVVKKQH/"
    "muZxKCp/"
    "4Xv3DQGLn0fI3sEerAPVTghAaaFyllgcDi1Asq43t6yzwI2IIKgHiOFKWjZyjZ3XZBMuAOJqYb"
    "TJVwwuDfIb/"
    "l8FR2cy5VX6Ts0HmZdunz90i7eClJZnjZdoMv1EjAMcFbLiYAT+"
    "x8TpX0DCeAHPXxAA5XTug7YiW7on9NPYPwgLtEEKiSNjcTg2y4YSehCeBv+"
    "xUZid98ne5khCmwHaQDGeOGfVZVgKwqgAiiBH4U2XAfTCco1qxNcAZxiOAm+J/"
    "kSvwEoYU4Anl325ath0hr5BYNPDYq9Sr4LzY+reJfBZZVa/vhPYRGGf2Z/"
    "p4bZZPfM++CmCFAF4YIETR/upnApw3AqUJAQ4ShQPD/"
    "ovA3wjdANDwwxvKZbVjN45uSwI427eqnIywpsbIKOT7iAAy4Ix+p5kxMn2kzSsCCKoA+"
    "AiwJoOOAJTtF8vPSAK3NSFLhAJdPwLuTKiwHc8jhsx+"
    "1YaGBSRxJdeadQgWETBVTJNG0mVEE3TbXww9yg6lmPzL/"
    "gapawNSitpXgIdcF40783tlzmUd94EAEiVAuc8m+HWOoCH61fxAy19R/"
    "mplAElHicqrryeD3wM1fVkpm1gBkOgxHEV0gZA4VnpiFlQ5MzHNNoXjpM+"
    "9APBozKuI59BvpgAwJgE/"
    "B0KA6CWgrP7vZP4bWcBJZJYEI1FYQuzlAtw8gTFg2jXs12I+diz7gQA9tu/"
    "2GaRkOQvrfYapiZgNR6znyMn1zQCkpG7GOZfG0PenQAAZIM6cS2bcq9osnxAC0C6AgH14+"
    "Ie9EIQQwoY5FRo0HAbbKY5In3Yf2QtHEGVWiGEAVhHow1cHPHgeJnAZqAIll3GrSUdKBkdyBmQ"
    "F41WTsxv3LMK6mAAe5bdwSKt6/"
    "AcCMEIAmevrbz88A7Dv1CofVQQ66w9ftAJrMdSuAHD46ucIiEGDeRDcKCwgB43KgZYa47l4biI"
    "av0QyybjfOufhWGcRiQHK7nivKQFUATcQ+Ylgnhl7+cT3sEOARgDO038dATjZ/"
    "w74AKTM9q05AScjBY8YEHRVy4/Kr4mEKZXbRnaSa/"
    "IAvR3HISk3CZkkr3AMOPeM3c2SiTtWAfyzgDyz3+xYZ/"
    "6e6XPoCMBZ9tuAboB8cALKIbT5x54H2CeVBrkGOHUFHjFQNlBJ6wnVZ+"
    "AWgogA3Fg6cVymuJ1zME/"
    "kYQdT0CwgXTUpEFdmUodtCgQQjrVf2NXtMuNn2lTu18x4rxyACgO8sp+n+ts+A+Rs+a+"
    "0Z1jFfXS/ASLLGQxjJEAYlgpn1FwdN0UazloDD6wR4aQVH4GTPP+ZCUkn/"
    "MmhxtWgsu7H7O9x5fkun/"
    "hsFQKw5B+"
    "AGsGfjfc9UrDIYjukmmjatlv4taoAFduvyccFWYJIvOSdFvIo7s8Avps0ScBaE606VoVUdFvL9"
    "byO4Inc2PvhnEcC2CfL+mf7p+P//"
    "ar1dgTsEA7AmJ1gFrZ36k36tXEjV8CshFwT3tEsqBPt2rDQNqX68GNl2kfEUQGmpcQR+"
    "VSOkQJIQf2vUMorxkxdd1R+hbl6aLzmAMhCnuEZAKPmrxW+"
    "EYAFcGtpsLM9dATgUrSiMvLQbSruYArQCaKIAJxyCjgxnGN6hGLuyy55npicFuEcJZSjAD7aPw"
    "vOK46TGfPBAej4nz3959T8B8VXYMR5aK4HIACOLD8DLZvzlp2nZiAB1G1+"
    "J9pVbD8jrdR6Awts5PymQL+Pf6j6EBCCNVHN/7iV/"
    "lgq6XkWCcn1k2NmwX2UxLLHyQBeLkPGXD7x3cccQGbdP1P9UPmt5CAAqiMLOVvD8re2XkjggHX"
    "ASALUWfAzl4BzKLT0wblk+kdt0vuNc6lMbBPkhtU9tMpRgfUogGaApfmi8lsdPd9S/"
    "44ASLyPQEelZwlATQqIPU/"
    "56ctB1MtEGI61slP1NybvU4LfELBXmxMZfzZGxnGkQY8HgB9rxkVM9XkK0imqfYUYqgRYAnHBE"
    "elxXzkAJwcg4EOFz9p+5hSasBPlZuGCMgIPIkwmiN50RjWg+"
    "22zDsFxHRnwR21cEKtzjADvTUx0OzMgjsY2VbEI/"
    "iq4ps+L3JiKslfPszJ2pS2exwMBZHMA+8Re709HAGxxELTtnACgWZNIa5ew/"
    "APY9c0xngno+qlBXHxfDP7tBlaOwSZjsn+"
    "GFLZJciAMOUQYRQI4dKxHBvWVJDAz9vKJz4rXAYjidiHA/"
    "sPRtQDWE4LGOwIt1e+"
    "2KxvgEsD7DPyotNPqXwQNO84ApIkxI3IJwXryMcPjnUAAVeCd1f6MaxsJgNX9WXjgKbzlCIwyX"
    "7vn3jJhpZCUAGBjRBCKTzjukoraOlfbp04iooTk04mFic4I6QiwvQkvp+"
    "XlL44cewYkZwF0uDZ1D2Ztu76VR8ZZPv5ZDxpOwwDr+"
    "X9P4ZV9b66B2HodRmgXnHEGrc8Tgz98B4GF4wJp0Bud7B+BqDu9fcxMn6hNaT+5llL/"
    "IsnNkMNMn9eZUDYC0M/"
    "5I2jXzxqowzaw9l1bZzsCl1p9I1zQJCHkhffeVH+HJBgA9HwysZYE4TA/Z/"
    "sZziECi+clPAXOKg62y5xLFHJMjZFU2ciVnA30GRJ4jD7Lxz/zVQ5AwFVa/"
    "rt3osAv5gIQ3A+25OFuenbefV6AlBLZeBb4U/"
    "hMNSLQC8gonPyzx7Xq7gapyObwfKJx4SfIOJmzjveYQM78VlW7PktU2eseCSCI9wegW5Y/"
    "SQwakDpksPYLM1juofVTQHFxE71NKGkJQmyGDTyt9qsFGeCYo8N5ZcfJtnMnsvo9smNm2mWBUH"
    "U50bFnjvvYY67H6wiAvvLLyQPgk3xWqKCFRZSdAbdti5KBilws8YrcAd70cgxfJYtAYQPI97uP"
    "Eog62DbxCmNGE7UKJjx2duwz2kVjXLl/hiAihzEz5isCCFYByhzRCj0A37H92xjE1neuwtmP/"
    "V1nQBYKWfMbQ40MCKvtD5EMO6ErgBqMGQGBnWa6z37sdPujoUYUipy4f9a+R0A/"
    "c9zl277bXgXYRQABjsDUIK0Anym7DiW0m2CCaS0ZHsggafuzYO6GSwCQNkn0CwnojDESYUwFjD"
    "jcTL9osVHZTTwigCMgvu77txCAEkCy7s9IAcHI3IIGNoJwIAV0ppmwYD+"
    "4xgn9HoCpAuIQl0aDsF9nH0J6KDWo2v5DKk86zxy/QjCZtq9Tm+hcrtq/"
    "EUCn9M4LQIYwYL+x5mpABUgK8H0jgmH47IC/"
    "U38Sl1fBnwV+GryzuYILwd+"
    "GTl5ENPmyzNONkzx2xg7PklP2ujLtHqtNdJxov3YljQBEibW1t7Y34CVW/"
    "Wngt3vv9MXxB4sPd5w5CBY+6PESTvihCUzU7JzF68uCwzrnSnKudCx1MZmJUxo/"
    "itWTP+bMeWX7PEW7s46ZGSdq00IA+"
    "uYfou4DkEG9vX2W7Weqz8gBccjcAQNPRfnNuUjcCQPB6a7BZIMqBI32SfBVjhZNtm6sxPFL48H"
    "glX5XtM2OeWa7zFhWm+VbP6NPAgrYXOX3VH8fwFT9qEqg+"
    "rvq76izRxQZfEVlQXcOJ4nDBdgZY6TZKoZ6ZpLFo4iq8JZHj1Htf1X7K8bNjDnTZiCAyPLPxvs"
    "4LnUEiaW/HaifCPyReEXEkSGfM22/nO82OaKTTyP4QMOLQo/"
    "M5NdnfXWf6viZ9pk263Vm2m0hwOoAUK3NxUCBsrvEkFH9YI1AN3+"
    "zFYHki0M6UBog8bCDYcth0SUHOgW3pwxyAPiJ9wvMjp6Z7Gzsx+pXPU62/RntGgFYyt/"
    "IQVnS9au3DwHL6vc6RIjWASDIBntvOMvsSkAPwBZuuu0HQBuNUwUFPd+LwZ+diFc4kPSxyQ/"
    "52H2rx6u0z7bV7ZZvkRyAEddr694BP3IFmXyAE/NHlt8iAv2fjXju1wJ/"
    "Cvhq4AzOzDZO58y4mXxClUxObX/"
    "4IvqzyU547xqOjnGkf7VvpX2p7bd8eCIJKIpLXAFTfq322jl0feCOee00qC2HYIHfUt408GFgb"
    "26n5v0JawVmiOVUgHuDpX6E+GwqEzseLRcnXz3OzDVV+3jtl5UAEKAIOhO40WO+"
    "mZifOA5KBEG7DuCJhUADIcDkZPPUJIQDil21/dP4KXYsNs9g46HNgYGrkz1/"
    "UucRwHrMo+c527/abwwBdgLoSIAou1bjSNU98jD/81Ct/t7/"
    "IyAuRPocAH9F9be2pEM0x+l+tTEag03u11H55Zy2yTZzURUUH2xbBVDmcEfGfOy+"
    "yzfrEMBaCrzfTAbsiBwyYcGg/"
    "oSEAOu9sKi2oe2fUP3WJQnacN4XbH84lp6VB9xJZoKn25RPPD3yaQ2PAC5zEkfHP9I/"
    "03cjAAbgAegHFv9YBMEsPyqsPgcNbNaWgb+bh4QsNLHgjWV9Q4IxZoZFIubxghmWcRWZSVrgj/"
    "xwb8Df/VYZMEY/"
    "7hVjPBAAgIIqvKHGkfJ3Y0UEsl99+L4AaQcoxLmm593Z4Gfz2pvrw76kg5giBXIiV+"
    "EwHDdsEE336/efAaiZszzzuEfHWr7508k7ARXIEMjMGZhKnnkpKGnDxhu2ESWfAX8K0Jn/"
    "ZwBmgjn3E7Y/"
    "i5uIWDITM3uszFgdYV01cPVEgvZHwXP0dK46fmXc5Zs+"
    "nZcBN8BFqn10v7H8V5NMZ7kTVYHBoicBTMkgqaqhC3AaRHiJ9m8TccJZeBM4dUw2wIHrjABVmd"
    "jkJ2nDV8eJzuus/"
    "VeelzX2RgCDwnuLghxV74CbedQ3Uy5MvBQkUn53P7odreIJUFnzvdueGKdq+b3xLwF2NqE/"
    "zRxnweiDNc6VpLD+Uo0AGnjBWg92f6dVur2yNFhA59h4nEfb5+"
    "T6fw2MCPxU9ZV8mG3UXKNzn1yjnqIRZtz9RXIpinaIplkiCgd+"
    "08D9Bc4ihuUbMQRQkzXrDBAv4UNBcllR+IDK/"
    "Ejgb5MZZnVEIJ7V9J4M9EAdEUI7ZqZhVrkzZJawFslTegPvR/"
    "gFMiSxEYBW2PX7oPIROWTe+JsIHzoygS/6fDTwjiq/"
    "Bv8s8BmJAOfR2x6BxnMW1dDBIyxrTkbnt/"
    "VzGqX6PwIgjhxCX0MGXEeO9xh912t4IIAo5nfAj2o0kAaqeDLb341hHNcDf/"
    "QEoAvsI8lCA4nW5D/iAE5558ABxR/O/SDCD3a/DCuZ83q/E8HyDZ/"
    "mVAF2pCEoKcizdj5DJEIaVfAnlgJXwT/lApxS3wzoM2DLTNSK8mfHE+UvtS/"
    "A9apxM6fwlMeW81vJ5WrnsREAA/W2LQHsVMyfGKez/"
    "gr8Q1ignEXm8V8PzFXXYIHJUmY2mWbIwPq/"
    "EvWEzkzeTJuQNMgg2XEzIJwJb6rjHgp7zjrYI43D3MryX8EBWHZ+VvUtEmGAbseAGUSPWwT/"
    "2apvglntOAv0bRwDWRnAXdYmM/"
    "BkEvKpgZm8tEeC7nWH6QhgRvVdkColt9rKcT1ioC4gsP0V8LttjUnMwFkBvjXJhu2EFGcBEk3s"
    "aL8cN5uHmD3PaMpnzzMax9v/"
    "GMc4cn5n9N0IANXXBWnmPQCi0Enwb8AO2mbAXwFw1fJXiKQBxLg7FYJAR8aGiyboZfvVwNFxMh"
    "N1ZoyZPplzie5hZYzXve3y9RICEBAOZJAEdQnQxpiuG3DWBWA//"
    "RnJhu5TdyskFTIDKwBPtU2qfwQGb3/Ut/"
    "utEo0TTUxczPSd6ZMF5pVjZ88hanfkHDcCiAC7HSAqFQJthi4icAlU8YMyImPtAcAOmLBtCHzC"
    "HikwR6GEvtMnVxQY6ZFD2vMt8TDTjFN5yj5Xgisa29t/BNSV4y5f/"
    "6nj04ADABNZfI8kqJor5XcVPwF+D7RybimSgF/"
    "PHDNQ5YhAPCC2vkl3EYF6VvlpP7VxZpJW+lTasntbAYLVduYcKse9evzoXJav+"
    "9RX6wBkMnUKfgH4U+VFDcTkcmANCAR/"
    "SBIF8M+"
    "CPOUUCDnijZwB9UyfDlSJmZpo0s3HTPtMm7McRMkNRcgK9s9e18HDDt03AugArx7qMfftQ0XKP"
    "+MmvD4U4HguhDi8PpV9mfUGTJFToJdrMGaGNWHO2u46iYCQjgAwC4RsuyxRZoA0c8xo3CvGjI7"
    "p3dvla4kD2Dqom06JIOsOEs8A4A9jOZCzwV9yBKpxBtSZNt01JY5h3cwzicA7p84VZGZech1AF"
    "hjZdjPneYTIop+iet7ReGed60YAFuBc9T8R/IPiF2N+Rh6RWtM+xEmIw/"
    "EmlEckacA6KnsGuL0JaO5LJv2ykztqF+2fBXV23LNApcc5cnyPCM4Yd/"
    "kv6ACyoM62q7wSTD+"
    "BaDiQlAuYLBNSIBeAGRGBSQbkTlZAf0bb4dySbqQ62TOTNtPGDVkIarJjnkkCR45Z/"
    "V1nHMPa5xUBwEQ/TfnhF3DHJC8TYa7gKPhLqg8Hi4Bd3W9ZbDZhzgB3ZYx2bs7szUzsqM3R/Y/"
    "pBqJzPZM0HgP4eD0bAaTi/WxeoBDvD6SQIAzG/"
    "K1bslJgEUF3o48+XUhi32EiFev8WYKYAjzOPBCDSFkicHj7o75Zlc+MQy4vurS2vzp+"
    "9ryvtveZ81i+"
    "5lPGMiBT3zRJ7J3Tig9UHvVxHYC6SxmQm22csVwC2q8lcgTbGGRWHQF4tq83KbYxjNkegWAW6N"
    "G4mUk84wYyx50Zt3K+FgFUzu2o+"
    "9gIIALeVeBHuxmdQxb8VeAP48IAEZCn9zvHsCZQFuDZdvQ4CeWPJudTE0F0fjNOoDLmEQKoHmf"
    "mWjRhLF8dOQA1KVygFpKDrwP4B7IwgDkNdOYIDJBlgXt2O7wPenJEE3IG7DN9qhM9Ou8rx5slg"
    "Mo5zzoT5hY2AjBBfTL48cfZhs6+"
    "OhzOvANtArBpR5AA5mEiIHc5GjPrCLLEcIXyW5O3uj07sTNgybTJgjU7Vna8KtEebe/1X/"
    "6z5QAmwT+AnL1g9CD4hTzcsMAiDba9mPCLQEv3G2RlTfoMoDNtvEnZ+"
    "quBZlR6Buwzx7lCvTMAz7SZIYDsuFlyZCrvnddGAIMDCMDfgbxCFIkKgUcg2q6m1X3/"
    "VWj7yTUD7Ec1iSHhLrJEcAT0dLIVKxHRRKwSQQSAq/"
    "dH15PdX2030z76LRj4oz7LV2kHQJRqIAgB1GOD31DRChF0bR3lM8GcKO91fYvuwmJr73y8yeQS"
    "RlL5zwL1rOJHk/jo/oxyR8e4GtDZ41fPoyeAQhKvVBk4Q/"
    "kD8FdIYLvhCTLxQozIAWzDBwCLQB3tj87BnQwTyl8hgkrbzKSNAHD1/"
    "gxJZNtkrhfVPLo2rfyV9hsBlMH8RMpfBjn8MpbyZ8asEEEbT/1GFZWOgB/"
    "tD13EBcpfBfwVbiCa+FfvrwA7OpfKWLNksZ7D8p8+lFwI9AS2H1U0A1Rp47YlwLTaTwF/"
    "7xSB9Oj+I+pfeX15SCYGyWYm5etGAhlQPmabqxwFjrsRgAaO+f0k5ccTcI+"
    "dBGuaHJLjReByCSNQ16PAj/qHgIUBKqrN2h7tH6ncFQQRgSoCeLQ/Gj+65gxxasufPSZrt/"
    "zHrAN4jcCfBjyG4RPPCZQdgAOuCLgeqUSEFIIeZt0VQD46pjeBryCBCMRX788CNjqPCplYx9wI"
    "IHQAB8GfVvwT3gNAgTQBflflme0l7qJCIDMgzwCvtQmcSZpECi82rTiECBTVsWbHi/"
    "pl9kdtzgT20bGW/xA5gNcc/K4bOAh8D8DdD3/"
    "kPygplhVLoL9Q+TPnESlUFdTV9rPOIgLw0f1HQRv9rjpE8I63EYDpAF5D8LuAP2j5o7GpSkMn/"
    "UNXvlfaZtxCa3Oh8lcAWWk7C9yzjpEFmAes2X3ZY2dIKNNm+"
    "feWA3hC8FeASNuS9QxZNbeOTfur38i6edkxI2BnVFc7kyPWPnO8yvhntI0m9WOSwBGQRy7g6P4"
    "skWwEMDiASfDjzTFdxX5m3f4CYCNyyCzwicZIkQUBv6fiFYWvtDVB9cjKnyWLqrqfBehZsM4Cc"
    "bZfFrjR+BFRynGWf6cdwCT4GahSJBCAPwJrtx++6GOnQK3icVO5T3p+oAL0qG13fYScvImVAW/"
    "p+CoIzYxfPb8qkUSAuIIgZseMzjWzP9NmPb+"
    "NABpYXgPwlwAPE02vZjwT8BHJsMn7ZG6AzLoMAM9qU7H5Z6j7GWNkVLd6nCwAFVe2r5HCn7V/"
    "+crVAVSeAUALbyjhrPJ7LsIC9NaHKN4lDsBQVtMpOI7CIyg2ebxjzKr/"
    "DOgzfSok8NhtI2CeCfQjID3SN7pG3L985cvEOgAE/"
    "ZFXfSceCio7AMO1uIShriflFhySqQL2DMKgx0yofwbAnnupALYCpsx5PUaY8H4ILSoAjxzG8hU"
    "vi88C7Ee3VB5PjrZJuA02BgVp4EBSwM7E/cn1BBVV90A2tQ86RQCOCCuz/ygRZAF/"
    "lETOBLSnypXz9Igssy8igIp7WP7tTgAhcCfVuyOBE8DfLq4A/shVuERhAGsKpBeFBNH/"
    "gmRNqogoov2PRQJHj/"
    "MYJDBDDkeAPHs8fcxGAJaiVwHMwLZtS4Df7Kst+8HKgQX44fj7hizYz24XKbH8rmjzItAe3R+"
    "dU9WmZ53AB5UEZoE8228ggH+TdQAFADMgpQhGAZ0SAlHkSOGj/"
    "VZ4MRNCZPvMtuv6JQgqA9gqKWTBmAV3tl32uGcpvgWy6vZZpT8L5CgQlAA85a2qtwZ6RflDB5A"
    "EfwT4aL+21Fb7LIhn+kfAzfzHIhVgR22j8zmq/BVQZc61SgKV41fH9n6bWXI4q9/"
    "y5SoJiAMfBb9Xm7ccwXB8cQVE7QayIW8groI0s5KwOmYEHm9Cm/suUP+MEp/"
    "V5oiaV8B6VdsZEphR9Jk+FXLYCMAE0oTtb2OpCZoBq+"
    "kAjLFMsgDP4x33TOsfugohMnJuEUEM56lmRaSIV+/"
    "PnP8RwGfHrxzjyrZnksPlBPBlRhlwxrpnwW8CnWXJC0RymBCS5b4zwV5Wf+hwBNhH+"
    "lqW9rHdwVF1P9r/"
    "dQZ6ljiWlQC0SjIbPLRRilYFv0cC7Yc9WOrLAFWf94y9n+"
    "ljnZurdie8YnzquMS9PAUJHAVshqCs63oMsFeuzzvPaB8eZ/"
    "lS7QCU4jJVNckgUGurH1XuiVJfilSYFTdUtUIgR0nA67/"
    "tU7OjouBll2GEKVnQZ4EWXUPFps8es3KM15EEskoPt3T7KP02AojUO0UCk+"
    "CnoCWAzII7Au2w3yG8o6COzoUBioKCnKPrFBjJqRlQcQLVY2WJIjNuBaCvIwlUVX0G0NVjdATw"
    "MXEAAYBdEnhC8Ecgc/efGPNH5xFNdhOQRdt/ptpHCh3tj675CFE8JTFUjv2UriFz7GUlgOp/"
    "DNKRwUHwdxPfUeMjDoCCq5BfOOoEZvpr2x+"
    "BLavolXEyAM6obnTMzHEqoMuc09HxKv2rbTPAVYZO/ydUbXfkKP4/"
    "BnecprBuissAAAAASUVORK5CYII=";

TexturePtr TextureTools::CreateResizedCopy(const TexturePtr& texture, int width,
                                           int height, bool useBilinearMode)
{
  auto scene  = texture->getScene();
  auto engine = scene->getEngine();

  auto rtt = RenderTargetTexture::New("resized" + texture->name, //
                                      ISize{width, height},      //
                                      scene,                     //
                                      !texture->noMipmap(),      //
                                      true,                      //
                                      texture->_texture->type,   //
                                      false,                     //
                                      texture->samplingMode(),   //
                                      false                      //
  );

  rtt->wrapU                     = texture->wrapU;
  rtt->wrapV                     = texture->wrapV;
  rtt->uOffset                   = texture->uOffset;
  rtt->vOffset                   = texture->vOffset;
  rtt->uScale                    = texture->uScale;
  rtt->vScale                    = texture->vScale;
  rtt->uAng                      = texture->uAng;
  rtt->vAng                      = texture->vAng;
  rtt->wAng                      = texture->wAng;
  rtt->coordinatesIndex          = texture->coordinatesIndex;
  rtt->level                     = texture->level;
  rtt->anisotropicFilteringLevel = texture->anisotropicFilteringLevel;
  rtt->_texture->isReady         = false;

  texture->wrapU = TextureConstants::CLAMP_ADDRESSMODE;
  texture->wrapV = TextureConstants::CLAMP_ADDRESSMODE;

  auto passPostProcess = PassPostProcess::New(
    "pass", 1.f, nullptr,
    useBilinearMode ? TextureConstants::BILINEAR_SAMPLINGMODE :
                      TextureConstants::NEAREST_SAMPLINGMODE,
    engine, false, EngineConstants::TEXTURETYPE_UNSIGNED_INT);
  passPostProcess->getEffect()->executeWhenCompiled([&](Effect* /*effect*/) {
    passPostProcess->onApply = [&](Effect* effect, EventState&) {
      effect->setTexture("textureSampler", texture);
    };

    auto internalTexture = rtt->getInternalTexture();

    if (internalTexture) {
      scene->postProcessManager->directRender({passPostProcess},
                                              internalTexture);

      engine->unBindFramebuffer(internalTexture);
      rtt->disposeFramebufferObjects();
      passPostProcess->dispose();

      internalTexture->isReady = true;
    }
  });

  return rtt;
}

BaseTexturePtr& TextureTools::GetEnvironmentBRDFTexture(Scene* scene)
{
  if (!scene->environmentBRDFTexture) {
#if 0
    auto texture = Texture::CreateFromBase64String(
      _environmentBRDFBase64Texture, "EnvironmentBRDFTexture", scene, true,
      false, TextureConstants::BILINEAR_SAMPLINGMODE);
#else
    auto texture
      = Texture::New("textures/_environmentBRDFBase64Texture.png", scene, true,
                     false, TextureConstants::BILINEAR_SAMPLINGMODE);
#endif

    texture->wrapU                = TextureConstants::CLAMP_ADDRESSMODE;
    texture->wrapV                = TextureConstants::CLAMP_ADDRESSMODE;
    texture->_texture->isReady    = true;
    scene->environmentBRDFTexture = texture;
  }

  return scene->environmentBRDFTexture;
}

} // end of namespace BABYLON
